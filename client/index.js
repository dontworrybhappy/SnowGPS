//hi
var bounds = [[0,0], [850, 1100]];
var map = L.map('mapid', {
    crs: L.CRS.Simple
}).setView([850/2, 1100/2], 0);
var image = L.imageOverlay('map.png', bounds).addTo(map);


var popup = L.popup();

function onMapClick(e) {
    popup
        .setLatLng(e.latlng)
        .setContent(e.latlng.toString())
        .openOn(map);
}

map.on('click', onMapClick);

navigator.geolocation.getCurrentPosition(function(location) {
  console.log(location.coords.latitude);
  console.log(location.coords.longitude);
  console.log(location.coords.accuracy);
});

L.polyline([
]).addTo(map);

L.circle(
[183, 418]
,{radius: 10}).addTo(map);

L.circle(
[668, 438]
,{radius: 10}).addTo(map);

L.circle(
[405, 1033]
,{radius: 10}).addTo(map);
