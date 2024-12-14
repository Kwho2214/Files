`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/08/2023 11:48:14 AM
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


module top_sim();
   reg btnC, btnD, btnU, btnL, btnR;
   reg [15:0] sw;
   reg clkin;
   
   top UUT(
   .btnC(btnC),
   .btnD(btnD),
   .btnU(btnU),
   .btnL(btnL),
   .btnR(btnR),
   .sw(sw),
   .clkin(clkin)
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
   btnD=0;
   btnL=0;
   btnU=0;
   btnR=0;
   btnC=0;
   #100000
   btnC=1;
   #1000000
   btnC=0;

   end
endmodule
