const db = require('../database');

const login = {
    checkPIN:function(login_kortti_nro, callback) {
        return db.query('select pin from kortti where kortti_nro=?', login_kortti_nro, callback);
    }
}

module.exports=login;