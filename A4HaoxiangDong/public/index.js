// Put all onload AJAX calls here, and event listeners
$(document).ready(function() {
    // On page-load AJAX Example
    $( "#uploadForm" ).hide();
     $( "#createfile" ).hide();
      $( "#createindi" ).hide();
       $("#createdes").hide();
       $("#createans").hide();
       $("#createDB").hide();
       $("#displayss").hide();
       
      // $('#clear').click();


    $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything
        url: '/uploads/',   //The server endpoint we are connecting to
        success: function (data) {
            /*  Do something with returned object
                Note that what we get is an object, not a string,
                so we do not need to parse it on the server.
                JavaScript really does handle JSONs seamlessly
            */
            //data = JSON.parse(data);
            // $.each( data, function( key, value ) {
            //       $('#text').val($('#text').val() + "You've just uploaded " +value);
            //     });
              //$('#text').val($('#text').val() + "You've just uploaded " +data);
            //We write the object to the console to show that the request was successful
            console.log(data);
        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error);
        }
    });
    //--
    /**
    $.ajax({
			  url:'/tryone',
			  type:'get',
			  data: {
			   fname:"fuck.ged",
			   source:"gygy",
			   gedcVersion:5.5,
			   encoding:"ASCII",
			   subName:"gygy",
			   subAddress:"gygy"
			   
			  },
			  success:function(data){
			   alert("fuck");
			  },
			  fail:function(error){
			   //do stuff
			  alert("fuck1111");
			  }
			 });
			 * */
    $('form[name="peopleform"]').submit(function(  ) {
	//alert("jj");
	//event.preventdefault();
	$('#text').val( $('#text').val() +"successful created a file " + $('input#filename').val() +"\n");
	return false;
		
});

    $('form[name="indiform"]').submit(function() {
	//alert("jj");
	//event.preventdefault();
	
	$('#text').val( $('#text').val() +"successful added " + $('input#given').val() + " " + $('input#surn').val() +" to " + $('#sel3').val() +"\n");

	return false;
		
});

  $('form[name="desform"]').submit(function() {
	//alert("jj");
	//event.preventdefault();
	
	$('#text').val( $('#text').val() +"successfully get descendant of " + $('input#given1').val() + " " + $('input#surn1').val() +" from " + $('#sel').val() +"\n");

	return false;
		
});

  $('form[name="ansform"]').submit(function() {
	//alert("jj");
	//event.preventdefault();
	
	$('#text').val( $('#text').val() +"successfully get ancestor of " + $('input#given2').val() + " " + $('input#surn2').val() +" from " + $('#sel2').val() +"\n");

	return false;
		
});

    $('form[name="uploadsub"]').submit(function(  ){
		//event.preventDefault();
		var filename = $('input[type=file]').val();
		$('#text').val( $('#text').val() +"successful uploaded a file " + filename +"\n");
		//return false;
		//alert(filename);
});
    
    

    
    
    //--

	//let datadroplist =[];
     $.ajax({
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything
           url: '/some',   //The server endpoint we are
    
               success: function (data) {
					var fields = data.split('|');
					
					for(var i = 0; i<fields.length; i++){
						if(fields[i].localeCompare("undefined") == 0){
							
							
						}else{
						

							
						//$('#text').val(fields[i]);
						$('#fileview').append('<tr><td><a href="/uploads/'+fields[i]+'">'+fields[i]+'</a></td><td>'+ fields[i+1] +'</td><td>' + 
						fields[i+2] +'</td><td>'+ fields[i+3] +'</td> <td>'+
						fields[i+4] +'</td><td>'+ fields[i+5] +'</td><td>'+
						fields[i+6] +'</td><td>'+ fields[i+7] +'</td></tr>' );
						i = i+8;
						//break;
					}
						
					}
                   //We write the object to the console to show that the request was successful
                   // console.log(data);
                   //$("#text").val(fields[1]);
                },
                fail: function(error) {
           // Non-200 return, do something with error
            console.log(error);
         }
     });

    // Event listener form replacement example, building a Single-Page-App, no redirects if possible
    // $('#uploadForm').submit(function(e){
    //     e.preventDefault();
    //   //  $.ajax({});
    //
    // });
    $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/people',   //The server endpoint we are connecting to
        success: function (data) {
				var fields = data.split('|');
				//alert(fields);
					for(var i = 0; i<fields.length; i++){
						if(fields[i].localeCompare("undefined") == 0 ||fields[i].localeCompare("people") == 0 ||fields[i].localeCompare("other") == 0 ||fields[i].localeCompare("") == 0){
							
							
						}else{
						//$('#text').val(fields[i]);
						$('#peopleview').append('<tr><td>'+ fields[i] +'</td><td>' + 
						fields[i+1] +'</td><td>'+ fields[i+3] +'</td> <td>'+
						fields[i+2] +'</td></tr>' );
						i = i+4;
						//break;
						
					}
						
					}
        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error); 
        }
    });

    $('#clear').click(function(e){
      $('#text').val("");
    });

    $('#bb').click(function(e){
      //$('#text').val($('#text').val() + "You've just uploaded\n");
      $( "#uploadForm" ).show();
      $( "#createfile" ).hide();
      $( "#createindi" ).hide();
      $("#createdes").hide();
      $("#createans").hide();
       $("#createDB").hide();
       $("#displayss").hide();


    });
    
        $('#des').click(function(e){
      //$('#text').val($('#text').val() + "You've just uploaded\n");
      $( "#uploadForm" ).hide();
      $( "#createfile" ).hide();
      $( "#createindi" ).hide();
      $("#createdes").show();
		$("#createans").hide();
		 $("#createDB").hide();
		 $("#displayss").hide();

    });
    
     $('#ans').click(function(e){
      //$('#text').val($('#text').val() + "You've just uploaded\n");
      $( "#uploadForm" ).hide();
      $( "#createfile" ).hide();
      $( "#createindi" ).hide();
      $("#createdes").hide();
	$("#createans").show();
	 $("#createDB").hide();
	 $("#displayss").hide();

    });
    
  $('#storeAll').click(function(e){
			/////
    $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/dataupfile',   //The server endpoint we are connecting to
        success: function (data) {
			
			$('#text').val( $('#text').val() +data +"\n");
			//---------------------
						
			$.ajax({
				type: 'get',            //Request type
				dataType: 'json',       //Data type - we will use JSON for almost everything 
				url: '/displaydb',   //The server endpoint we are connecting to
				success: function (data) {
			$('#displayText').val(data+"\n");
        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error); 
        }
    });
			
			//--------------------------------
			
        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error); 
        }
    });
    /////
    });
    
    //
    
        
  $('#clearDB').click(function(e){
			/////
    $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/dbclear',   //The server endpoint we are connecting to
        success: function (data) {
			$('#text').val( $('#text').val() +data +"\n");
			//---------------------------
			$.ajax({
				type: 'get',            //Request type
				dataType: 'json',       //Data type - we will use JSON for almost everything 
				url: '/displaydb',   //The server endpoint we are connecting to
				success: function (data) {
			$('#displayText').val(data+"\n");
        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error); 
        }
    });
    //-----------------------
    
    
        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error); 
        }
    });
 
});
    
    
    //
     $('#datebase').click(function(e){
		
		$("#createDB").show();
		      $( "#uploadForm" ).hide();
      $( "#createfile" ).hide();
      $( "#createindi" ).hide();
      $("#createdes").hide();
	$("#createans").hide();
	 $("#displayss").hide();
	// $("#createDB").hide();

    });
    
     $('#displayDB').click(function(e){
		
	  $("#createDB").show();
	  $( "#uploadForm" ).hide();
      $( "#createfile" ).hide();
      $( "#createindi" ).hide();
      $("#createdes").hide();
	$("#createans").hide();
	$("#displayss").show();
	 $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/displaydb',   //The server endpoint we are connecting to
        success: function (data) {
			$('#displayText').val(data+"\n");
        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error); 
        }
    });
	
	// $("#createDB").hide();

    });
    
     $('#coll').click(function(e){
      //$('#text').val($('#text').val() + "You've just uploaded\n");
      $( "#uploadForm" ).hide();
      $( "#createfile" ).hide();
      $( "#createindi" ).hide();
      $("#createdes").hide();
	$("#createans").hide();
	 $("#createDB").hide();
	 $("#displayss").hide();

    });
    
    $('#addindi').click(function(e){
      //$('#text').val($('#text').val() + "You've just uploaded\n");
      $( "#createfile" ).hide();
      $( "#uploadForm" ).hide();
      $( "#createindi" ).show();
       $("#createdes").hide();
       $("#createans").hide();
        $("#createDB").hide();
        $("#displayss").hide();



    });

      $('#create').click(function(e){
      //$('#text').val($('#text').val() + "You've just uploaded\n");
      $( "#createfile" ).show();
      $( "#uploadForm" ).hide();
      $( "#createindi" ).hide();
       $("#createdes").hide();
       $("#createans").hide();
        $("#createDB").hide();
        $("#displayss").hide();



    });
    
    
    $('#bylastname').click(function(e){
      //$('#text').val($('#text').val() + "You've just uploaded\n");
		 $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/sortedname',   //The server endpoint we are connecting to
			success: function (data) {
				$('#querytext').val(data+"\n");
			},
			fail: function(error) {
            // Non-200 return, do something with error
				console.log(error); 
			}
		});



    });
    
    $('#bynopeople').click(function(e){
      //$('#text').val($('#text').val() + "You've just uploaded\n");
		 $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/sortednumpeople',   //The server endpoint we are connecting to
			success: function (data) {
				$('#querytext').val(data+"\n");
			},
			fail: function(error) {
            // Non-200 return, do something with error
				console.log(error); 
			}
		});



    });
    $('#byF').click(function(e){
      //$('#text').val($('#text').val() + "You've just uploaded\n");
		 $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/sortedbyF',   //The server endpoint we are connecting to
			success: function (data) {
				$('#querytext').val(data+"\n");
			},
			fail: function(error) {
            // Non-200 return, do something with error
				console.log(error); 
			}
		});



    });
     $('#byM').click(function(e){
      //$('#text').val($('#text').val() + "You've just uploaded\n");
		 $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/sortedbyM',   //The server endpoint we are connecting to
			success: function (data) {
				$('#querytext').val(data+"\n");
			},
			fail: function(error) {
            // Non-200 return, do something with error
				console.log(error); 
			}
		});



    });
     $('#byai').click(function(e){
      //$('#text').val($('#text').val() + "You've just uploaded\n");
		 $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/findbyal',   //The server endpoint we are connecting to
			success: function (data) {
				$('#querytext').val(data+"\n");
			},
			fail: function(error) {
            // Non-200 return, do something with error
				console.log(error); 
			}
		});



    });
    $('#byu8').click(function(e){
      //$('#text').val($('#text').val() + "You've just uploaded\n");
		 $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/findbyu8',   //The server endpoint we are connecting to
			success: function (data) {
				$('#querytext').val(data+"\n");
			},
			fail: function(error) {
            // Non-200 return, do something with error
				console.log(error); 
			}
		});



    });
    $('#byue').click(function(e){

      //$('#text').val($('#text').val() + "You've just uploaded\n");
		 $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/findbyue',   //The server endpoint we are connecting to
			success: function (data) {
				$('#querytext').val(data+"\n");
			},
			fail: function(error) {
            // Non-200 return, do something with error
				console.log(error); 
			}
		});



    });
    $('#byal').click(function(e){
      //$('#text').val($('#text').val() + "You've just uploaded\n");
		 $.ajax({
			type: 'get',            //Request type
			dataType: 'json',       //Data type - we will use JSON for almost everything 
			url: '/findbyall',   //The server endpoint we are connecting to
			success: function (data) {
				$('#querytext').val(data+"\n");
			},
			fail: function(error) {
            // Non-200 return, do something with error
				console.log(error); 
			}
		});
  });
  
  
	$('#subsql').click(function(e){
        var filename = $('#filename').val();
        console.log(filename);
        /*
        if (!filename || files.includes(filename) || !subname) {
            log('Invalid arguments');
            return;
        }
        */
        $.ajax({
			url: '/submitsql',
            type: 'get',
            data: {
                filename: filename
            },
            //dataType: 'json',
            
            success: function(x) {
                $('#querytext').val(x+"\n");
            }
        });
    });
    
    
	$('#byspfile').click(function(e){
        var spfile= $('#aspfile').val();
      
        /*
        if (!filename || files.includes(filename) || !subname) {
            log('Invalid arguments');
            return;
        }
        */
        $.ajax({
			url: '/submitsp',
            type: 'get',
            data: {
                spfile: spfile
            },
            dataType: 'json',
            
            success: function(data) {
                $('#querytext').val(data+"\n");
            }
        });
    });

	$('#sublogin').click(function(e){
        var host= $('#ghost').val();
        var user= $('#guser').val();
        var password= $('#gpassword').val();
        var database= $('#gdatabase').val();
        
        if (!host || !user || !password) {
            log('Invalid arguments');
            return;
        }
       
        $.ajax({
			url: '/submitlogin',
            type: 'get',
            data: {
                host: host,
                user: user,
                password: password,
                database: database,
            },
            dataType: 'json',
            
            success: function(data) {
                $('#logtext').val(data+"\n");
            }
        });
    });
$('#fresh').click(function(e){

    $.ajax({
            type: 'get',            //Request type
            dataType: 'json',       //Data type - we will use JSON for almost everything
           url: '/some',   //The server endpoint we are
    
               success: function (data) {

					var fields = data.split('|');
					//console.log(data);
					for(var i = 0; i<fields.length; i++){
						if(fields[i].localeCompare("undefined") == 0){
							
							
						}else{
						

							
						//$('#text').val(fields[i]);
						$('#fileview').append('<tr><td><a href="/uploads/'+fields[i]+'">'+fields[i]+'</a></td><td>'+ fields[i+1] +'</td><td>' + 
						fields[i+2] +'</td><td>'+ fields[i+3] +'</td> <td>'+
						fields[i+4] +'</td><td>'+ fields[i+5] +'</td><td>'+
						fields[i+6] +'</td><td>'+ fields[i+7] +'</td></tr>' );
						i = i+8;
						//break;
					}
						
					}
                   //We write the object to the console to show that the request was successful
                   // console.log(data);
                   //$("#text").val(fields[1]);
                },
                fail: function(error) {
           // Non-200 return, do something with error
            console.log(error);
         }
     });

    // Event listener form replacement example, building a Single-Page-App, no redirects if possible
    // $('#uploadForm').submit(function(e){
    //     e.preventDefault();
    //   //  $.ajax({});
    //
    // });
    $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/people',   //The server endpoint we are connecting to
        success: function (data) {
				var fields = data.split('|');
				//alert(fields);
					for(var i = 0; i<fields.length; i++){
						if(fields[i].localeCompare("undefined") == 0 ||fields[i].localeCompare("people") == 0 ||fields[i].localeCompare("other") == 0 ||fields[i].localeCompare("") == 0){
							
							
						}else{
						//$('#text').val(fields[i]);
						$('#peopleview').append('<tr><td>'+ fields[i] +'</td><td>' + 
						fields[i+1] +'</td><td>'+ fields[i+3] +'</td> <td>'+
						fields[i+2] +'</td></tr>' );
						i = i+4;
						//break;
						
					}
						
					}
        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error); 
        }
    });

    });





  

});
