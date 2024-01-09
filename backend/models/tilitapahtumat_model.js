const db = require('../database');

const tilitapahtumat = {

  getAll: function(callback) {
    return db.query('select * from tilitapahtumat', callback);
  },
  
  getByKortti_nro: function(kortti_nro, callback) {
    return db.query('select * from asiakkaantilitapahtumat where kortti_nro=? order by idtilitapahtumat desc limit 10', [kortti_nro], callback);
  },

  add: function(tilitapahtumat, callback) { //Ei toimi postmanissa, toimii SQL:ssä.
    return db.query(
      'CALL LisaaTapahtuma(?,?,?)',
      [tilitapahtumat.idTili, tilitapahtumat.tapahtuma, tilitapahtumat.maara], callback);
  },
/*
  add: function(tilitapahtumat, callback) { //tätä pitänee muuttaa.
    return db.query(
      'insert into tilitapahtumat (pvm, tapahtuma, maara, idtili) values(?,?,?,?)',
      [tilitapahtumat.pvm, tilitapahtumat.tapahtuma, tilitapahtumat.maara, tilitapahtumat.idtili], callback);
  },*/

  delete: function(id, callback) {
    return db.query('delete from tilitapahtumat where idtilitapahtumat=?', [id], callback);
  },

  update: function(id, tilitapahtumat, callback) {
    return db.query(
      'update tilitapahtumat set pvm=?, tapahtuma=?, maara=? where idtilitapahtumat=?',
      [tilitapahtumat.pvm, tilitapahtumat.tapahtuma, tilitapahtumat.maara, id], callback);
  }

};
module.exports = tilitapahtumat;