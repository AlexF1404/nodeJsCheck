import express from 'express'
import path from 'path'
import { createRequire } from 'module';
const require = createRequire(import.meta.url)
const addon = require('./build/Release/addon');
var bodyParser = require('body-parser');
var urlencodedParser = bodyParser.urlencoded({extended: false});

const __dirname = path.resolve()
const PORT = 3000;
const app = express();

app.get('/', (req, res) => {
  res.sendFile(path.resolve(__dirname, 'template', 'main.html'))
})


app.post('/checkUser', urlencodedParser, (req, res) => {
  var itUser = addon.addon(req.body.nameUser)
  if (itUser==true)
  {
    res.sendFile(path.resolve(__dirname, 'template', 'userFound.html'))
  }
  else
  {
    res.sendFile(path.resolve(__dirname, 'template', 'userNotFound.html'))
  }
})

app.listen(3000, () => {
    console.log(`Порт сервера:  ${PORT}`);
});
