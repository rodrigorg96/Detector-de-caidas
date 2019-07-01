$(document).ready(function(){
    var intervaloConsulta = setInterval(function(){consulta();},3000);
    
    function consulta(){
        $.get('consulta.php',{none:'NULL'},function(response){
            var str = response;   
            $('#C').text(str);
            if(str=="0")
                {
                    $('#C').text("No se ha detectado caida");
                }
                else{
                    $('#C').text("Caida detectada");}
            
            }
            
        );
            
        }
    
});

