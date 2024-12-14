`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/20/2023 12:57:48 PM
// Design Name: 
// Module Name: led_sim
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module led_sim(

    );
    reg clk, Go, btnU, showled;
    
    ledstatemachine UUT(
    .clk(clk),
    .Go(Go),
    .qsec(clk),
    .showled(showled)
    );
    
   initial    // Clock process for clkin
    begin
        #20
		  clk = 1'b1;
        forever
        begin
            #50 clk = ~clk;
        end
    end     

    initial
    begin
    
    Go=1;
    btnU=0;
    load=0;
    #50000
    load=1;
    #2000
    load=0;
   
    
    end
    
endmodule
