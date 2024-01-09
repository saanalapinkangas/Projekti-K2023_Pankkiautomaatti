const db = require('../database');

const tili = {
  getAll: function(callback) {
    return db.query('select * from tili', callback);
  },
  /*
  getByKortti_nro: function(kortti_nro, callback) {
    return db.query('select * from asiakkaantilitapahtumat where kortti_nro=? order by idtilitapahtumat desc limit 5', [kortti_nro], callback);
  },*/

  getByKortti_nro: function(kortti_nro, callback) {
    return db.query('select Etunimi, Sukunimi, idTili, DebitTilinro, CreditTilinro, DebitSaldo, CreditSaldo, PVM, Tapahtuma, Maara, idTilitapahtumat from asiakkaantilitapahtumat where kortti_nro=? order by idTilitapahtumat desc limit 5', [kortti_nro], callback);
  },
/*
  add: function(tili, callback) {
    return db.query(
      'insert into tili (debitTilinro, debitSaldo, creditTilinro, creditSaldo, creditLuottoraja) values(?,?,?,?,?)',
      [tili.debittilinro, tili.debitsaldo, tili.credittilinro, tili.creditsaldo, tili.creditluottoraja], callback);
  },*/
  
  add: function(tili, callback) { // Toimii muuten postmanissa, mutta ei printtaa virheilmoitusta, jos saldo ei riitä. Ei kyllä updateta tai postaa tili-taulua tai tilitapahtumat-taulua.
    return db.query(
      'CALL LisaaTapahtuma2(?,?,?)',
      [tili.idTili, tili.tapahtuma, tili.maara], callback);
  },

  delete: function(id, callback) {
    return db.query('delete from tili where idtili=?', [id], callback);
  },
  
  update: function(id, tili, callback) {
    return db.query(
      'update tili set debitTilinro=?, debitSaldo=?, creditTilinro=?, creditSaldo=?, creditLuottoraja=? where idtili=?',
      [tili.debittilinro, tili.debitsaldo, tili.credittilinro, tili.creditsaldo, tili.creditluottoraja, id], callback);
  }

};
module.exports = tili;