const db = require('../database');

const asiakas = {
  
  getAll: function(callback) {
    return db.query('select * from asiakas', callback);
  },
/*
  getById: function(id, callback) {
    return db.query('select * from asiakas where idasiakas=?', [id], callback);
  },*/
  
  getByKortti_nro: function(kortti_nro, callback) {
    return db.query('select Etunimi, Sukunimi, DebitTilinro, CreditTilinro from asiakkaantilitapahtumat where kortti_nro=?', [kortti_nro], callback);
  },
  
  add: function(asiakas, callback) {
    return db.query(
      'insert into asiakas (henkilotunnus, etunimi, sukunimi, puhelinnumero, osoite) values(?,?,?,?,?)',
      [asiakas.henkilotunnus, asiakas.etunimi, asiakas.sukunimi, asiakas.puhelinnumero, asiakas.osoite], callback);
  },

  delete: function(id, callback) {
    return db.query('delete from asiakas where idasiakas=?', [id], callback);
  },

  update: function(id, asiakas, callback) {
    return db.query(
      'update asiakas set henkilotunnus=?,etunimi=?, sukunimi=?, puhelinnumero=?, osoite=? where idasiakas=?',
      [asiakas.henkilotunnus, asiakas.etunimi, asiakas.sukunimi, asiakas.puhelinnumero, asiakas.osoite, id], callback);
  }

};
module.exports = asiakas;