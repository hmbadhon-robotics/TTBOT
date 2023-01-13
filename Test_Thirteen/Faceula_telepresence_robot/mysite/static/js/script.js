function run_function(param1, param2){
    console.log("running");
    $.ajax({
        url : "mysite/", // the endpoint
        type : "GET", // http method
        data : { param_first : param1, 
                param_second : param2 }, // data sent with the get request

        // handle a successful response
        success : function(json) {
            console.log("success"); // another sanity check
        },

        // handle a non-successful response
        error : function(xhr,errmsg,err) {
            console.log(xhr.status + ": " + xhr.responseText); // provide a bit more info about the error to the console
        }
    });
};