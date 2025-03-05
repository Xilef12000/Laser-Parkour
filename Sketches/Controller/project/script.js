var socket;
function onload() {
    switch(new URLSearchParams(location.search).get("m")) {
        case "game":
            game();
            break;	
        case "setup":
            setup();
            break;
        default:
            window.location.replace(location.origin + "?m=setup")
    }
}
function rescan() {
    fetch('http://192.168.4.1:5000/action/rescan')
    .then(response => {
        if (!response.ok) {
            throw new Error("HTTP error " + response.status);
        }
    })
    .catch(function () {
        this.dataError = true;
    })
}
function submitName() {
    fetch('http://192.168.4.1:5000/action/name?name=' + document.getElementById("name").value)
    .then(response => {
        if (!response.ok) {
            throw new Error("HTTP error " + response.status);
        }
    })
    .catch(function () {
        this.dataError = true;
    })
}
function lostConnection() {
    console.error('lost Connection');
    document.getElementById('lostConnection').hidden = false;
    socket.close()
    setTimeout(function() {window.location.reload();}, 3000);
}
function reconnectedSensor() {
    const msg = document.getElementById('reconnectedSensor');
    msg.hidden = false;
    setTimeout(function() {msg.hidden = true;}, 3000);
}
function game() {
    lostSensor = document.getElementById('lostSensor');
    nameSubmit = document.getElementById('nameSubmit');
    startGameFirst = document.getElementById('startGameFirst');
    stateLabel = document.getElementById('stateLabel');
    document.getElementById('game').hidden = false;
    //const socket = new WebSocket('ws://' + location.host + '/API/game');
    socket = new WebSocket('ws://' + "192.168.4.1:5000" + '/API/game');
    timeout = setTimeout(lostConnection, 1000);
    socket.addEventListener('message', ev => {
        clearTimeout(timeout);
        socket.send('.');
        timeout = setTimeout(lostConnection, 1000);
        data = JSON.parse(ev.data);
        //console.log(data);
        switch(data["systemStateMachine"]) {
            case 1:
                stateLabel.innerHTML = "waiting for name";
                break;
            case 2:
                stateLabel.innerHTML = "waiting for start";
                break;
            case 3:
                stateLabel.innerHTML = "game running";
                break;
            case 0:
            default:
                // code block
        } 
        if (data["sensorState"] == -1) {
            if (lostSensor.hidden == true) {
                lostSensor.hidden = false;
                console.error("lost connection to sensor")
            }
        }
        else {
            if (lostSensor.hidden == false) {
                lostSensor.hidden = true;
                reconnectedSensor()
            }
        }
        if (data["systemMode"] == 0 || data["systemStateMachine"] == 0) {
            if (startGameFirst.hidden == true) {
                startGameFirst.hidden = false;
            }
        }
        else {
            if (startGameFirst.hidden == false) {
                startGameFirst.hidden = true;
            }
        }
        if (data["systemStateMachine"] == 1) {
            if (nameSubmit.disabled == true) {
                nameSubmit.disabled = false;
                fetchPlayerlist();
            }
        }
        else {
            if (nameSubmit.disabled == false) {
                nameSubmit.disabled = true;
            }
        }
    });
    socket.addEventListener('close', ev => {
        console.log('<<< closed');
        lostConnection()
    });
    fetchPlayerlist();
}
function fetchPlayerlist() {
    fetch('http://192.168.4.1:5000/API/playerlist')
    .then(response => {
        if (!response.ok) {
            throw new Error("HTTP error " + response.status);
        }
        return response.json();
    })
    .then(list => {
        lastList = document.getElementById('lastList');
        topList = document.getElementById('topList');
        //console.log(list);
        table = '<table>'
        table += '<tr>'
        table += '<th>Name:</th>'
        table += '<th>Time:</th>'
        table += '<th>Interrupted:</th>'
        table += '<th>Total Time:</th>'
        table += '</tr>'
        list.lastList.reverse().forEach(element => {
            table += '<tr>'
            table += '<td>' + element.name + '</td>'
            table += '<td>' + element.delta + '</td>'
            table += '<td>' + element.interrupted + '</td>'
            table += '<td>' + element.time + '</td>'
            table += '</tr>'
        });
        table += '</table>'
        lastList.innerHTML = table

        table = '<table>'
        table += '<tr>'
        table += '<th>#</th>'
        table += '<th>Name:</th>'
        table += '<th>Time:</th>'
        table += '<th>Interrupted:</th>'
        table += '<th>Total Time:</th>'
        table += '</tr>'
        list.topList.forEach((element, n) => {
            table += '<tr>'
            table += '<td>' + String(n + 1) + '</td>'
            table += '<td>' + element.name + '</td>'
            table += '<td>' + element.delta + '</td>'
            table += '<td>' + element.interrupted + '</td>'
            table += '<td>' + element.time + '</td>'
            table += '</tr>'
        });
        table += '</table>'
        topList.innerHTML = table
    })
    .catch(function () {
        this.dataError = true;
    })
}
function startGame() {
    socket.close()
    setTimeout(() => {window.location.replace(location.origin + "/action/startgame")}, 1500)
}
function setup() {
    document.getElementById('setup').hidden = false;
    div = document.getElementById('sensors');
    //const socket = new WebSocket('ws://' + location.host + '/API/sensors');
    socket = new WebSocket('ws://' + "192.168.4.1:5000" + '/API/sensors');
    timeout = setTimeout(lostConnection, 1000);
    socket.addEventListener('message', ev => {
        clearTimeout(timeout);
        socket.send('.');
        timeout = setTimeout(lostConnection, 1000);
        table = '<table>'
            
            table += '<tr>'
                table += '<th>Addr</th>'
                table += '<th>Type</th>'
                table += '<th>Mode</th>'
                table += '<th>Value</th>'
                table += '<th>conStatus</th>'
                table += '</tr>'
        if (ev.data == ']') {
            //console.log("no sensor connected")
            table += '<tr><td>--</td></tr>'
        }
        else {
            data = JSON.parse(ev.data)
            //console.log(data)
            
            for (var i in data) {
                table += '<tr>'
                    table += '<td>' + data[i].address + '</td>'
                    table += '<td>' + data[i].deviceType + '</td>'
                    table += '<td>' + data[i].deviceMode + '</td>'
                    table += '<td>' + data[i].value + '</td>'
                    table += '<td>' + data[i].conStatus + '</td>'
                    table += '</tr>'
                }	
            }
        table += '</table>'
        div.innerHTML = table
    });
    socket.addEventListener('close', ev => {
        console.log('<<< closed');
        lostConnection()
    });
}