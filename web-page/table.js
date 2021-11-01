setInterval(load_json, 3000);
var url = "table.json";
var nocach_count = 0;
function load_json() {
	var xmlhttp = new XMLHttpRequest();
	xmlhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			parsed_json = JSON.parse(this.responseText);
			console.log(parsed_json);
			//var list = parsed_json.place1.name;
			//document.getElementById("Top").innerHTML = list;
		}
	}
}
xmlhttp.open("GET", url + "?nocache=" + nocach_count, true);
xmlhttp.send();
console.log("loaded json :" + "?nocache=" + nocach_count);
nocach_count ++;