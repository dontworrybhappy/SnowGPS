var express = require('express')
var exec = require('child_process').exec;
var app = express()
    
    app.get('/snow', function(req, res) {
          // here we would call the dijkstras program and pipe in my location.  assuming the form: startx,starty,endx,endy
          var list = req.query.loc.split(",");
          exec('pwd', function callback(error, stdout, stderr){
              res.json({path: stdout, queries:list})
          });
    })
 
app.listen(3000)
