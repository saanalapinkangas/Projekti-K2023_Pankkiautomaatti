const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds=10;
const kortti = {
  
  getAll: function(callback) {
    return db.query('select * from kortti', callback);
  },
  
  getByKortti_nro: function(kortti_nro, callback) { //tämä näyttäis toimivan
    return db.query('select * from kortti where kortti_nro=?', [kortti_nro], callback);
  },
/*
  add: function(kortti, callback) {   // ilman cryptausta, testi
  return db.query(
      'insert into kortti (kortti_nro, pin, idasiakas, idtili) values(?,?,?,?)',
      [kortti.kortti_nro, kortti.pin, kortti.idasiakas, kortti.idtili],callback);
  },
  */

  add: function(kortti, callback) {   // PIN-koodin cryptaus toimii.
    bcrypt.hash(kortti.pin, saltRounds, function(err,hash) {
    return db.query(
      'insert into kortti (idkortti, kortti_nro, pin, idasiakas, idtili) values(?,?,?,?,?)',
      [kortti.idkortti, kortti.kortti_nro, hash, kortti.idasiakas, kortti.idtili], callback);
  })
},

  delete: function(id, callback) {
    return db.query('delete from kortti where idkortti=?', [id], callback);
  },

 /* update: function(id, kortti, callback) {  //ilman cryptausta, testi
    return db.query(
      'update kortti set pin=?, idasiakas=?, idtili=? where idkortti=?',
      [kortti.pin, kortti.idasiakas, kortti.idtili, id], callback);
},*/

  update: function(id, kortti, callback) {
    bcrypt.hash(kortti.pin, saltRounds, function(err,hash) {
    return db.query(
      'update kortti set kortti_nro=?, pin=? where idkortti=? and idtili=8', //täällä määritetty idtili=8, koska halusin just sitä tiliä updateta.
      [kortti.kortti_nro, hash, id], callback);
    })
  },

};
module.exports = kortti;