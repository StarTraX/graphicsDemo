/* jshint -W099 */ //remove warning about mixed spaces and tabs???
var URL = "http://192.168.0.4:8080/dashboard/wind/readTwdBackground.php";	
Pebble.addEventListener("ready",load_data); //deleted for case 
function load_data(){
	//var url = "http://192.168.0.4:8080/dashboard/readWindDirImage.php"; // gets current course as formatted text string
	/*
	var http = new XMLHttpRequest(); 
	http.open("GET", URL, true);
	http.send(null);
	http.onreadystatechange = function () {
		  if (http.readyState == 4 ){
			   	if(http.status == 200){ // or 404 not found	
					var windDirBackgroundImage = JSON.parse( http.responseText);					
					//console.log("http.responseText: " + windDirBackgroundImage[24]);
						//console.log("windDirBackgroundImage[24]: " + windDirBackgroundImage[24]);
						Pebble.sendAppMessage({ 
							"0": windDirBackgroundImage//formatted TWD Background bit array										   					   
								}, function(e) { //Success callback								
									//console.log("Sent OK: ")  ;
									getWind();
								},
								function(e) { //Fail callback	
									console.log("Sent FAILED")  ; 
								
							}
						);
				}
				else
			Pebble.showSimpleNotificationOnPebble("HTTP Fail(2)", "Check that your web server is running on "+WEB_HOST); 	
		  }
		};
		*/
	getWind();
}

function getWind(){
	/*
	var url = "http://192.168.0.4:8080/dashboard/readWindDirImage.php"; // gets current course as formatted text string
	var http = new XMLHttpRequest(); 
	http.open("GET", url, true);
	http.send(null);
	http.onreadystatechange = function () {
		  if (http.readyState == 4 ){
			   	if(http.status == 200){ // or 404 not found	
					var windDirImageS = JSON.parse( http.responseText);	
					//console.log("responseText: " + http.responseText);
					var windDirImageRecent = windDirImageS.windDirImageRecent;
					console.log("windDirImageRecent JSON: " +JSON.stringify( windDirImageRecent));
					var arrayLength = windDirImageRecent.length;;
					windDirImageRecent = [1,2,3,4,5,6,7,8,9];
					console.log("windDirImageRecent.length:"+windDirImageRecent.length )
					Pebble.sendAppMessage({ 
							//"201": windDirImageRecent//compressed last 10 mins TWD image bit array										   					   
							//"201": "12345"//compressed last 10 mins TWD image bit array		
						  "201": windDirImageRecent
								}, function(e) { //Success callback								
									console.log("Sent windDirImageRecent OK ")  ;
									looper();
								},
								function(e) { //Fail callback	
								console.log("Sent FAILED")  ; 								
							}
						);
				}
				else
			Pebble.showSimpleNotificationOnPebble("HTTP Fail(2)", "Check that your web server is running on "+WEB_HOST); 	
		  }
		};
		*/
						windDirImageRecent = [1,2,3,4,5,6,7,8,9];		
						Pebble.sendAppMessage({ 
						  "201": windDirImageRecent
								}, function(e) { //Success callback								
									console.log("Sent windDirImageRecent OK ")  ;
									looper();
								},
								function(e) { //Fail callback	
								console.log("Sent FAILED")  ; 								
							}
						);
}



var start = 205;
function looper(){
	Pebble.sendAppMessage({ 
		"1": start // SW //updated place to start the wind background display									   					   
			}, function(e) { //Success callback								
				//console.log("Sent start OK: "+start)  ;
				if (start < 360){
					start += 1;	
					//document.setTimeout(looper(),500);
					//setTimeout(function(){looper();},500); 
				}
			},
			function(e) { //Fail callback	
				console.log("Sent FAILED")  ; 		
		}
	);	
}

	