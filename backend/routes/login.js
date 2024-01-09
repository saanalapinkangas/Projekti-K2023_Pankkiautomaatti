const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const login = require('../models/login_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.kortti_nro && request.body.pin) {
      const user = request.body.kortti_nro;
      const pass = request.body.pin; // pass on käyttäjän syöte.
      
        login.checkPIN(user, function(err, dbResult) {
          if(err){
            response.json(err.errno); //err.erro, jotta printtaa vain virhenumeron.
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(pass,dbResult[0].pin, function(err,compareResult) {
                if(compareResult) {
                  console.log("succes");
                  const token = generateAccessToken({ kortti_nro: user }); 
                  response.send(token);
                }
                else {
                    console.log("wrong PIN");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("user does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("username or PIN missing");
      response.send(false);
    }
  }
);

function generateAccessToken(kortti_nro) {
  dotenv.config();
  return jwt.sign(kortti_nro, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router;