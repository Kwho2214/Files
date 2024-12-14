`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/23/2023 12:34:42 PM
// Design Name: 
// Module Name: led_shift
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


module led_shift(

    );
    reg clk;
    reg enable;
    reg dir;
    reg load_tar;
    reg reset;
    
    
    led_shifter UUT(
    .clk(clk),
    .enable(enable),
    .dir(dir),
    .load_tar(load_tar),
    .reset(reset)
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
    enable=0;
    dir=0;
    load_tar=0;
    #500
    ;
//    enable=1;
//    dir=0;
//    load_tar=1;
//    #500
//    enable=0;
//    dir=0;
//    load_tar=0;
//    #500
//    enable=1;
//    dir=1;
//    load_tar=1;
//    #500
//    enable=0;
//    dir=0;
//    load_tar=0;
//    #500
//    enable=0;
//    dir=1;
//    load_tar=1;
    end
endmodule
