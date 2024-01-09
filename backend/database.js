const dotenv=require('dotenv');
const mysql = require('mysql2');
dotenv.config();

const connection=mysql.createPool(process.env.SQL_SERVER);

/*const connection = mysql.createPool({
  host: '127.0.0.1',
  user: 'automaatti',
  password: 'salasana',
  database: 'atm'
});*/

module.exports = connection;