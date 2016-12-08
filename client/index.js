var METERS_PER_PIXEL = 2

var bounds = [[0,0], [850, 1100]];
var map = L.map('mapid', {
    crs: L.CRS.Simple
}).setView([850/2, 1100/2], 0);
var ready = false;

var image = L.imageOverlay('map.png', bounds).addTo(map);
var me = L.circle( [183, 418], {radius: 10}).addTo(map);
var dest = L.circle( [18399, 41899],
{radius: 10, color: '#33ff88'}).addTo(map);
var course = L.polyline([
]).addTo(map);

var popup = L.popup();

function onMapClick(e) {
    dest.setLatLng(e.latlng);
    popup
        .setLatLng(e.latlng)
        .setContent('Destination')
        .openOn(map);
    ready = true;
    gps();
}

map.on('click', onMapClick);

var geo_options = {
  enableHighAccuracy: true, 
  maximumAge        : 30000, 
  timeout           : 27000
};

var watchID = navigator.geolocation.watchPosition(function(po) {
var lat = po.coords.latitude;
var lon = po.coords.longitude;
var hagarltlat = 41.70508;
var hagarltlon = -86.23719;
var hagarltx = 557;
var hagarlty = 151;
var yconv = (41.69296 - 41.70635) / 800;
var xconv = (-86.22375 - -86.24727) / 1000;
var y = (lat - hagarltlat)/yconv + hagarlty;
var x = (lon - hagarltlon)/xconv + hagarltx;
me.setLatLng([850 - y, x]);
me.setRadius(po.coords.accuracy / METERS_PER_PIXEL);
gps();
}, function(){}, geo_options);


function gps() {
    if (!ready) return;
    //TODO: Make API Request
    var xhr = new XMLHttpRequest();
    var mel = me.getLatLng();
    var del = dest.getLatLng();
    loc = "" + mel.lat + "," + mel.lng + "," +  del.lat + "," + del.lng;
    xhr.open('GET', "https://www.johnbot.me/snow?loc=" + loc, true);
    xhr.send();
     
    xhr.addEventListener("readystatechange", function (e){
        if (xhr.readyState == 4 && xhr.status == 200) {
            console.log(xhr.responseText);
            var returnedList = JSON.parse(xhr.responseText);
            course.setLatLngs(returnedList);
        }
    }, false);
}
