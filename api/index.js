var express = require('express')
var exec = require('child_process').exec;
var app = express()

    app.use(function(req, res, next) {
        res.header("Access-Control-Allow-Origin", "*");
        res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
        next();
    });

    app.get('/snow', function(req, res) {
          // here we would call the dijkstras program and pipe in my location.  assuming the form: startx,starty,endx,endy
          var list = req.query.loc.split(",");
          var strold = "echo '";
          for( var i in list){
              strold += list[i] + " ";
          }
          strold += "' | ./shortestpath/dijkstras ";
          console.log(strold);
          exec(strold, function callback(error, stdout, stderr){
              res.json({path: stdout, queries:list})
          });
    })
  
app.listen(3000)
