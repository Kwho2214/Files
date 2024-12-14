`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/22/2023 12:44:07 PM
// Design Name: 
// Module Name: top_sim
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


module top_sim(

    );
    reg clkin, btnU, btnC, btnL, btnR, btnD;
    reg [15:0] sw;
    wire [15:0] led;
    wire [3:0] an;
    wire [6:0] seg;
    
    toplvl UUT (
    .clkin(clkin),
    .btnU(btnU),
    .btnC(btnC),
    .btnL(btnL),
    .btnD(btnD),
    .btnR(btnR),
    .sw(sw),
    .led(led),
    .an(an),
    .seg(seg)
    );
    
     initial    // Clock process for clkin
    begin
        #20
		  clkin = 1'b1;
        forever
        begin
            #50 clkin = ~clkin;
        end
    end     

    initial
    begin
    btnC=0;
    btnD=0;
    btnL=0;
    btnR=0;
    btnU=0;
    sw=0;
    #500
    btnD=1;
    #200
    btnD=0;
    #15000
    btnC=1;
    #500
    btnL=1;
    btnC=0;
    #100
    btnL=0;
    #1000
    btnL=1;
    #100
    btnL=0;
       #1000
    btnL=1;
    #100
    btnL=0;
       #1000
    btnL=1;
    #100
    btnL=0;
       #1000
    btnL=1;
    #100
    btnL=0;
       #1000
    btnL=1;
    #100
    btnL=0;
       #1000
    btnL=1;
    #100
    btnL=0;
    end
endmodule
