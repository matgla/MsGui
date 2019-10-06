"use strict";

var process = require("process");

var options = {
    owner: "matgla",
    repo: "MsGui",
    path: "page/ci/data/binary_size.json"
};

var GithubDB = require('..').default;

var db = new GithubDB(options);

db.auth(process.env.GITHUB_DB_TOKEN);
db.connectToRepo();

var query_by_name = {
    name: "size_data"
};

var options = {
    multi: false,
    upsert: true
};

db.find(query_by_name).then((results) => {
    console.log(results);
    // var old_data = results.data;
  //  db.update(query_by_name, {data: })
});

// db.update(query, )