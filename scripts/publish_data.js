"use strict";

var process = require("process");

var options = {
    owner: "matgla",
    repo: "MsGui",
    path: "page/ci/data/binary_size.json"
};

var GithubDB = require("github-db").default;

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
    if (results.length < 1 || results.undefined)
    {
        console.log("Empty")
        var empty_data = {
            name: "size_data",
            data: [1]
        };
        db.save(empty_data).then((res) => {
            console.log("Updated");
        });
    }
    console.log("data:", results[0].data);

   db.update(query_by_name, {data: result[0].data.append(result[0].data[data.length - 1] + 1)})
});

// db.update(query, )