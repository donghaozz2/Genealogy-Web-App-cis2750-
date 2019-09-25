'use strict'

//----
const mysql = require('mysql');
var connection = mysql.createConnection({
    host     : 'dursley.socs.uoguelph.ca',
    user     : 'hdong04',
    password : '0850990',
    database : 'hdong04'
});

connection.connect();

//--make a new table

connection.query("CREATE TABLE IF NOT EXISTS FILE(file_id INT NOT NULL AUTO_INCREMENT, file_Name VARCHAR(60) NOT NULL, source VARCHAR(250) NOT NULL, version VARCHAR(10) NOT NULL, encoding VARCHAR(10) NOT NULL, sub_name VARCHAR(62) NOT NULL, sub_addr VARCHAR(256) NOT NULL, num_individuals INT, num_families INT, PRIMARY KEY ( file_id ))", function (err, rows, fields) {    
  
    if (err) 
        console.log("Something went wrong. "+err);
    else {
        console.log("Sucessfully created FILE");

    }

});
connection.query("CREATE TABLE IF NOT EXISTS INDIVIDUAL(ind_id INT NOT NULL AUTO_INCREMENT, surname VARCHAR(256) NOT NULL, given_name VARCHAR(256) NOT NULL, sex VARCHAR(1), fam_size INT, source_file INT, PRIMARY KEY ( ind_id ), FOREIGN KEY (source_file) REFERENCES FILE(file_id) ON DELETE CASCADE)", function (err, rows, fields) {    
  
    if (err) 
        console.log("Something went wrong. "+err);
    else {
        console.log("Successfully created INDIVIDUAL");

    }

});


//--
//----
// C library API
const ffi = require('ffi');

// Express App (Routes)
const express = require("express");
const app     = express();
const path    = require("path");
const fileUpload = require('express-fileupload');

app.use(fileUpload());

// Minimization
const fs = require('fs');
const JavaScriptObfuscator = require('javascript-obfuscator');

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

//----------------
/*	
	var returnVal = "";
	connection.connect(function(err) {
		if(err) {
			console.log("Unable to connect");
			//res.send("Unable to connect");
			returnVal = "Unable to connect";
		}
		else{
			var file = "CREATE TABLE IF NOT EXISTS FILE(file_id INT NOT NULL AUTO_INCREMENT, file_Name VARCHAR(60) NOT NULL, source VARCHAR(250) NOT NULL, version VARCHAR(10) NOT NULL, encoding VARCHAR(10) NOT NULL, sub_name VARCHAR(62) NOT NULL, sub_addr VARCHAR(256) NOT NULL, num_individuals INT, num_families INT, PRIMARY KEY ( file_id ))";
			connection.query(file, function(err, result) {
				if(err) {
					console.log("Unable to create FILE");
					//res.send("Unable to connect");
					//returnVal = "Unable to connect";
				}
				else{
					console.log("Sucessfully created FILE");
					
					var indivs = "CREATE TABLE IF NOT EXISTS INDIVIDUAL(ind_id INT NOT NULL AUTO_INCREMENT, surname VARCHAR(256) NOT NULL, given_name VARCHAR(256) NOT NULL, sex VARCHAR(1), fam_size INT, source_file INT, PRIMARY KEY ( ind_id ), FOREIGN KEY (source_file) REFERENCES FILE(file_id) ON DELETE CASCADE)";
					connection.query(indivs, function(err, result) {
						if(err) {
							console.log("Unable to create INDIVIDUAL");
						}
						else{
							console.log("Successfully created INDIVIDUAL");
						}
					});
				}
			});
			
			//var individuals = 
			
			console.log("Connected successfully");
			//res.send("Connected successfully");
			//returnVal = "Connected successfully";
		}
});
*/

// Send HTML at root, do not change
app.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/public/index.html'));
});

// Send Style, do not change
app.get('/style.css',function(req,res){
  //Feel free to change the contents of style.css to prettify your Web app
  res.sendFile(path.join(__dirname+'/public/style.css'));
});

// Send obfuscated JS, do not change
app.get('/index.js',function(req,res){
  fs.readFile(path.join(__dirname+'/public/index.js'), 'utf8', function(err, contents) {
    const minimizedContents = JavaScriptObfuscator.obfuscate(contents, {compact: true, controlFlowFlattening: true});
    res.contentType('application/javascript');
    res.send(minimizedContents._obfuscatedCode);
  });
});

//Respond to POST requests that upload files to uploads/ directory
app.post('/upload', function(req, res) {
  if(!req.files) {
    return res.status(400).send('No files were uploaded.');
  }

  let uploadFile = req.files.uploadFile;
//let sampleFile = req.files.sampleFile;
  // Use the mv() method to place the file somewhere on your server
  uploadFile.mv('uploads/' + uploadFile.name, function(err) {
    if(err) {
      return res.status(500).send(err);
    }else{
      console.log(uploadFile);
    }

    res.redirect('/');
  });
});
//Respond to GET requests for files in the uploads/ directory
app.get('/uploads/:name', function(req , res){
  fs.stat('uploads/' + req.params.name, function(err, stat) {
    console.log(err);
    if(err == null) {
      res.sendFile(path.join(__dirname+'/uploads/' + req.params.name));
    } else {
      res.send('');
    }
  });
});

let sharedLib = ffi.Library('./testlib', {
  'tryf' : [ 'string', [] ],
  'gedinformation' : [ 'string', ['string'] ],
  'gedinaboutpeople' : [ 'string', ['string'] ],
   'makeadecom' :[ 'string',['string'] ],
   'gedputdata' :[ 'string',['string'] ],
   'gedinaboutpeopleDB':[ 'string',['string','int'] ],

});

//******************** Your code goes here ********************


var lastfile=0;

 const testFolder = "./uploads/"
 var fileArray = [];
 let one;
 let all;
 var person;
 let allpeople;

 fs.readdir('./uploads/', (err, files) => {
   files.forEach((file) => {
    fileArray.push(file);
    person=sharedLib.gedinaboutpeople(file);
    one=sharedLib.gedinformation(file);
    all=all+one;
    allpeople=allpeople+ person;
    var array = fs.readFileSync(testFolder + file).toString().split("\n");

   });
 });
 
 
 
 
   //all=all+allpeople;
app.get('/people', function(req , res){
	//////////////////////////////////

 /////////////////////////////
  res.send(
   
    JSON.stringify(allpeople)
  );
});
var dbupfile;



app.get('/dataupfile', function(req , res){
	var f=0;
	var some="";
	var number=0;
	var allnum2=0;
	for(;fileArray[f];)
	{
		

		
		dbupfile=sharedLib.gedputdata(fileArray[f]);
		//console.log(dbupfile);
		connection.query(dbupfile, function (err, rows, fields) {    
  
			if (err) 
			{
				console.log("Something went wrong. "+err);
				
				
			}
			else {
				console.log("Sucessfully updata file");

			}

		});
		f=f+1;
		
	}
	console.log(f);

	connection.query("select * from FILE order by file_id", function (err, rows, fields) {
		var fileid=0;
		var finame;
		var allpeople;
		
	var putpeople= [];
		if (err) 
		{
			console.log("Something went wrong. "+err);
			
		}
		else {
				//console.log("Database contents sorted by id:");

      
				for (let row of rows){
					//console.log("ID: "+row.file_id+" Last name: "+row.file_Name+" source: "+row.source+" version: "+row.version +" encoding: "+row.encoding+" sub_name: "+row.sub_name+" sub_addr: "+row.sub_addr+" num_individuals: "+row.num_individuals+" num_families: "+row.num_families);
					fileid=row.file_id;
					lastfile=row.file_id;
					finame=row.file_Name;
					allpeople=sharedLib.gedinaboutpeopleDB(finame,fileid);
					
					putpeople=allpeople.split("|");
					console.log(putpeople);
					number=0;
					for(;putpeople[number];)
					{
						
						console.log(putpeople[number]);
						if(putpeople[number]!='null')
						{
							//console.log(putpeople[number]);
							connection.query(putpeople[number], function (err, rows, fields) {

								if (err) 
								{
									console.log("Something went wrong. "+err);
									//some=some+"Something went wrong. ";
								}
								else {
									console.log("Sucessfully updata a person");//
									//some=some+"Sucessfully updata a person\n";
									
								}


								});
								allnum2=allnum2+1;
								console.log(allnum2);
						}
						number++;
					}

           
           
			}
        
        
        
        
		}

 
console.log(f);

some="sent "+ f+" files to database\n"+"send "+allnum2+" people to database";
	res.send(
		
		JSON.stringify(some)
  );
	});
	
	//console.log(number);

});

app.get('/dbclear', function(req , res){
	var some="";
		connection.query("delete from FILE", function (err, rows, fields) {

			if (err) 
				console.log("Something went wrong. "+err);
			else {
				console.log("Database FILE ALL REMOVE");
			}
		});
		connection.query("delete from INDIVIDUAL", function (err, rows, fields) {

			if (err) 
				console.log("Something went wrong. "+err);
			else {
				console.log("Database INDIVIDUAL ALL REMOVE");

			}


		});
		some="Database FILE ALL REMOVE\n"+"Database INDIVIDUAL ALL REMOVE";
		res.send(
		
			JSON.stringify(some)
		);
});
//--dis play db
 app.get('/displaydb', function(req , res){
	connection.query("select * from FILE order by file_id", function (err, rows, fields) {
		var infile="";
		var inpeople="";
		var numf=0;
		var nump=0;
		var back="";
		if (err) 
			console.log("Something went wrong. "+err);
		else {
			console.log("Database contents sorted by id:");

		  
			for (let row of rows){
				//console.log("ID: "+row.file_id+" file_name: "+row.file_Name+" source: "+row.source+" version: "+row.version +" encoding: "+row.encoding+" sub_name: "+row.sub_name+" sub_addr: "+row.sub_addr+" num_individuals: "+row.num_individuals+" num_families: "+row.num_families);
				infile=infile+"ID: "+row.file_id+" file_name: "+row.file_Name+" source: "+row.source+" version: "+row.version +" encoding: "+row.encoding+" sub_name: "+row.sub_name+" sub_addr: "+row.sub_addr+" num_individuals: "+row.num_individuals+" num_families: "+row.num_families+"\n";
				numf=numf+1;
			}
		}

		connection.query("select * from INDIVIDUAL order by ind_id", function (err, rows, fields) {

			if (err) 
				console.log("Something went wrong. "+err);
			else {
				console.log("Database contents sorted by id:");

			  
				for (let row of rows){
					//console.log("ID: "+row.ind_id+" surname: "+row.surname+" given_name: "+row.given_name+" sex: "+row.sex +" fam_size INT: "+row.fam_size+" source_file: "+row.source_file);
					inpeople=inpeople+"ID: "+row.ind_id+" surname: "+row.surname+" given_name: "+row.given_name+" sex: "+row.sex +" fam_size INT: "+row.fam_size+" source_file: "+row.source_file+"\n";
					nump=nump+1;
				}
				
			}
		//console.log(inpeople);
		//console.log(infile);
		//console.log(numf);
		//console.log(nump);
			back="Database has "+ numf+" files and "+nump+" individuals\n"+"------------------\n"+infile+"------------------\n"+inpeople+"------------------\n" ;
			//console.log(back);
			res.send(
				JSON.stringify(back)
			);
		});

	});
});
  //--
 //--
 app.get('/sortedname', function(req , res){
	var back="ID      sex    fam    Id_file     given+lastname\n";
	connection.query("select * from INDIVIDUAL order by surname", function (err, rows, fields) {

		if (err) 
			console.log("Something went wrong. "+err);
		else {
			console.log("Database contents sorted by lastname:");

			  
			for (let row of rows){
				//console.log("ID: "+row.ind_id+" surname: "+row.surname+" given_name: "+row.given_name+" sex: "+row.sex +" fam_size INT: "+row.fam_size+" source_file: "+row.source_file);
				back=back+row.ind_id+"      "+row.sex +"      "+row.fam_size+"       "+row.source_file+"      "+row.given_name+" "+row.surname+"\n";
				
			}
				
		}
		//console.log(inpeople);
		//console.log(infile);
		//console.log(numf);
		//console.log(nump);
			
			
			res.send(
				JSON.stringify(back)
			);
		});

});
 app.get('/sortednumpeople', function(req , res){
	var back="ID      num_people      filename  fam_size\n";
	connection.query("select *  from FILE,INDIVIDUAL WHERE INDIVIDUAL.source_file=FILE.file_id AND INDIVIDUAL.sex='F' order by num_individuals", function (err, rows, fields) {

		if (err) 
			console.log("Something went wrong. "+err);
		else {
			console.log("Database contents sorted by lastname:");

			  
			for (let row of rows){
				//console.log("ID: "+row.ind_id+" surname: "+row.surname+" given_name: "+row.given_name+" sex: "+row.sex +" fam_size INT: "+row.fam_size+" source_file: "+row.source_file);


				back=back+row.file_id+"        "+row.num_individuals +"               "+row.file_Name+"   "+ row.fam_size+"\n";
			}
				
		}
		//console.log(inpeople);
		//console.log(infile);
		//console.log(numf);
		//console.log(nump);
			//console.log(back);
			
			res.send(
				JSON.stringify(back)
			);
		});

});
 app.get('/sortedbyF', function(req , res){
	var back="ID      FILE_id      SEX      name\n";
	connection.query("select *  from INDIVIDUAL WHERE INDIVIDUAL.sex='F' order by surname", function (err, rows, fields) {

		if (err) 
			console.log("Something went wrong. "+err);
		else {
			console.log("Database contents sorted by lastname:");

			  
			for (let row of rows){
				//console.log("ID: "+row.ind_id+" surname: "+row.surname+" given_name: "+row.given_name+" sex: "+row.sex +" fam_size INT: "+row.fam_size+" source_file: "+row.source_file);
				back=back+row.ind_id+"      "+row.source_file+"          "+row.sex+"      "+row.given_name+" "+row.surname+"\n";
			}
				
		}
		//console.log(inpeople);
		//console.log(infile);
		//console.log(numf);
		//console.log(nump);
			//console.log(back);
			
			res.send(
				JSON.stringify(back)
			);
		});

});
 app.get('/sortedbyM', function(req , res){
	var back="ID      FILE_id      SEX      name\n";
	connection.query("select *  from INDIVIDUAL WHERE INDIVIDUAL.sex='M' order by surname", function (err, rows, fields) {

		if (err) 
			console.log("Something went wrong. "+err);
		else {
			console.log("Database contents sorted by lastname:");

			  
			for (let row of rows){
				//console.log("ID: "+row.ind_id+" surname: "+row.surname+" given_name: "+row.given_name+" sex: "+row.sex +" fam_size INT: "+row.fam_size+" source_file: "+row.source_file);
				back=back+row.ind_id+"      "+row.source_file+"          "+row.sex+"      "+row.given_name+" "+row.surname+"\n";
			}
				
		}
		//console.log(inpeople);
		//console.log(infile);
		//console.log(numf);
		//console.log(nump);
			//console.log(back);
			
			res.send(
				JSON.stringify(back)
			);
		});

});
 app.get('/findbyal', function(req , res){
	var back="encoding   SEX        file_name    person_name \n";
	connection.query("select *  from INDIVIDUAL,FILE WHERE INDIVIDUAL.source_file=FILE.file_id AND FILE.encoding='ASCII'", function (err, rows, fields) {

		if (err) 
			console.log("Something went wrong. "+err);
		else {
			console.log("Database contents sorted by lastname:");

			  
			for (let row of rows){
				//console.log("ID: "+row.ind_id+" surname: "+row.surname+" given_name: "+row.given_name+" sex: "+row.sex +" fam_size INT: "+row.fam_size+" source_file: "+row.source_file);
				back=back+row.encoding+"         "+row.sex+"     "+row.file_Name+"    "+row.given_name+" "+row.surname+"\n";
			}
				
		}
		//console.log(inpeople);
		//console.log(infile);
		//console.log(numf);
		//console.log(nump);
			//console.log(back);
			
			res.send(
				JSON.stringify(back)
			);
		});

});
 app.get('/findbyu8', function(req , res){
	var back="encoding   SEX        file_name    person_name \n";
	connection.query("select *  from INDIVIDUAL,FILE WHERE INDIVIDUAL.source_file=FILE.file_id AND FILE.encoding='UTF8'", function (err, rows, fields) {

		if (err) 
			console.log("Something went wrong. "+err);
		else {
			console.log("Database contents sorted by lastname:");

			  
			for (let row of rows){
				//console.log("ID: "+row.ind_id+" surname: "+row.surname+" given_name: "+row.given_name+" sex: "+row.sex +" fam_size INT: "+row.fam_size+" source_file: "+row.source_file);
				back=back+row.encoding+"         "+row.sex+"     "+row.file_Name+"    "+row.given_name+" "+row.surname+"\n";
			}
				
		}
		//console.log(inpeople);
		//console.log(infile);
		//console.log(numf);
		//console.log(nump);
			//console.log(back);
			
			res.send(
				JSON.stringify(back)
			);
		});

});
 app.get('/findbyue', function(req , res){
	var back="encoding   SEX        file_name    person_name \n";
	connection.query("select *  from INDIVIDUAL,FILE WHERE INDIVIDUAL.source_file=FILE.file_id AND FILE.encoding='UNICODE'", function (err, rows, fields) {

		if (err) 
			console.log("Something went wrong. "+err);
		else {
			console.log("Database contents sorted by lastname:");

			  
			for (let row of rows){
				//console.log("ID: "+row.ind_id+" surname: "+row.surname+" given_name: "+row.given_name+" sex: "+row.sex +" fam_size INT: "+row.fam_size+" source_file: "+row.source_file);
				back=back+row.encoding+"      "+row.sex+"     "+row.file_Name+"    "+row.given_name+" "+row.surname+"\n";
			}
				
		}
		//console.log(inpeople);
		//console.log(infile);
		//console.log(numf);
		//console.log(nump);
			//console.log(back);
			
			res.send(
				JSON.stringify(back)
			);
		});

});
 app.get('/findbyall', function(req , res){
	var back="encoding   SEX        file_name    person_name \n";
	connection.query("select *  from INDIVIDUAL,FILE WHERE INDIVIDUAL.source_file=FILE.file_id AND FILE.encoding='ANSEL'", function (err, rows, fields) {

		if (err) 
			console.log("Something went wrong. "+err);
		else {
			console.log("Database contents sorted by lastname:");

			  
			for (let row of rows){
				//console.log("ID: "+row.ind_id+" surname: "+row.surname+" given_name: "+row.given_name+" sex: "+row.sex +" fam_size INT: "+row.fam_size+" source_file: "+row.source_file);
				back=back+row.encoding+"         "+row.sex+"     "+row.file_Name+"    "+row.given_name+" "+row.surname+"\n";
			}
				
		}
		//console.log(inpeople);
		//console.log(infile);
		//console.log(numf);
		//console.log(nump);
			//console.log(back);
			
			res.send(
				JSON.stringify(back)
			);
		});

});
//--


app.get('/submitsql', function(req, res) {
  let filename = req.query.filename;
  var some=filename;
  console.log(some);
  var back="submit Sucessfully";
 
  	connection.query(some, function (err, rows, fields) {

		if (err) 
		{
			console.log("Something went wrong. "+err);
			back="Something went wrong. "+err;
			res.send(
				JSON.stringify(back)
			);
		}
		else {
			console.log("Database contents sorted by lastname:");

			  
			for (let row of rows){
				//console.log("ID: "+row.ind_id+" surname: "+row.surname+" given_name: "+row.given_name+" sex: "+row.sex +" fam_size INT: "+row.fam_size+" source_file: "+row.source_file);
				
			}
			
			res.send(
				JSON.stringify(rows)
			);
		}

			

		});
 // console.log(filename);

});

app.get('/submitsp', function(req, res) {
  let spfile = req.query.spfile;
  var some=spfile;
  console.log(some);
  var putin="select *  from INDIVIDUAL,FILE WHERE INDIVIDUAL.source_file=FILE.file_id AND FILE.file_Name='"+some+"'";
  var back="filename           sex     fam    name \n";
 
  	connection.query(putin, function (err, rows, fields) {

		if (err) 
		{
			console.log("Something went wrong. "+err);
			back="Something went wrong. "+err;
			res.send(
				JSON.stringify(back)
			);
		}
		else {
			console.log("Database contents sorted by lastname:");

			  
			for (let row of rows){
				//console.log("ID: "+row.ind_id+" surname: "+row.surname+" given_name: "+row.given_name+" sex: "+row.sex +" fam_size INT: "+row.fam_size+" source_file: "+row.source_file);
				back=back+row.file_Name+"    "+row.sex+"     "+row.fam_size+"    "+row.given_name+" "+row.surname+"\n";
			}
			res.send(
				JSON.stringify(back)
			);
		
		}

			

		});
 // console.log(filename);

});


app.get('/submitlogin', function(req, res) {
  let host = req.query.host;
  var ghost=host;
  console.log(ghost);
  
  let user = req.query.user;
  var guser=user;
  console.log(guser);
  
  let password = req.query.password;
  var gpassword=password;
  console.log(gpassword);
  
  let database = req.query.database;
  var gdatabase=database;
  console.log(gdatabase);
  
  
  connection.end();
 
	connection = mysql.createConnection({
		host     : ghost,
		user     : guser,
		password : gpassword,
		database : gdatabase
	});

	connection.connect();
 
	//--make a new table

	connection.query("CREATE TABLE IF NOT EXISTS FILE(file_id INT NOT NULL AUTO_INCREMENT, file_Name VARCHAR(60) NOT NULL, source VARCHAR(250) NOT NULL, version VARCHAR(10) NOT NULL, encoding VARCHAR(10) NOT NULL, sub_name VARCHAR(62) NOT NULL, sub_addr VARCHAR(256) NOT NULL, num_individuals INT, num_families INT, PRIMARY KEY ( file_id ))", function (err, rows, fields) {    
	  
		if (err) 
		{
			console.log("Something went wrong. "+err);
			res.send(
				JSON.stringify("Fall to login and you logout!")
			);
		}	
		else {
			console.log("Sucessfully created FILE");
			connection.query("CREATE TABLE IF NOT EXISTS INDIVIDUAL(ind_id INT NOT NULL AUTO_INCREMENT, surname VARCHAR(256) NOT NULL, given_name VARCHAR(256) NOT NULL, sex VARCHAR(1), fam_size INT, source_file INT, PRIMARY KEY ( ind_id ), FOREIGN KEY (source_file) REFERENCES FILE(file_id) ON DELETE CASCADE)", function (err, rows, fields) {    
	  
				if (err) 
					console.log("Something went wrong. "+err);
				else {
					console.log("Successfully created INDIVIDUAL");
					res.send(
						JSON.stringify("Successfully to login and I create FILE and INDIVIDUAL TABLE if you do not have!")
					);	
				}

			});
		}

	});

  
});









  /*
var back;

  app.get('/tryone', function(req , res){
    const fname= req.query.fname;
  const source= req.query.source;
  const gedcVersion= req.query.gedcVersion;
  const encoding= req.query.encoding;
  const subName= req.query.subName;
  const subAddress= req.query.subAddress;
   // const firstName = req.query.firstName;
    //const lastName = req.query.lastName;
    var agedcom=fname+"|"+"{\"source\":\""+source+"\",\"gedcVersion\":\""+gedcVersion+"\",\"encoding\":\""+encoding+"\",\"subName\":\""+subName+"\",\"subAddress\":\""+subAddress+"\"}-";
    
    console.log(agedcom);
 back=sharedLib.makeadecom(agedcom);
 console.log(back);
   res.send(
   
    JSON.stringify(back)
  );
   
});
  */
//--
  app.get('/some', function(req , res){
	  //////////////////////////////////////////////
	  
	  fileArray = [];
allpeople="";
	   fs.readdir('./uploads/', (err, files) => {
   files.forEach((file) => {
    fileArray.push(file);
    person=sharedLib.gedinaboutpeople(file);
 
    one=sharedLib.gedinformation(file);

    all=all+one;
    allpeople=allpeople+ person;
    var array = fs.readFileSync(testFolder + file).toString().split("\n");

   });
 });
	
	 ///////////////////////////////////////// 

    res.send(
      JSON.stringify(all)
    );
  });
app.get('/uploads/', function(req , res){
  res.send({
    fileArrayList: fileArray,
  //  foo: "bar"
  });
});



app.listen(portNum);
console.log('Running app at localhost: ' + portNum);

//--
//connection.end();

//--

