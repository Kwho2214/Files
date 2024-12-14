`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/02/2023 11:05:03 AM
// Design Name: 
// Module Name: state_sim
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


module state_sim();
    reg clk, btnC, btnD, btnL, btnR, freeze;
    
    playerstate UUT (
    .clk(clk),
    .btnC(btnC),
    .btnD(btnD),
    .btnL(btnL),
    .btnR(btnR),
    .freeze(freeze)
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
   freeze=0;
   btnC=0;
   btnD=0;
   btnL=0;
   btnR=0;

   
   //begin game
   btnC=0;
   #200
   btnC=1;
   #200
   btnC=0;
   
   //go right
//   btnR=0;
//   #100
//   btnR=1;
//   Rborder=0;
//   #200
//   Rborder=1;
//   btnR=0;
   //go left
//   btnL=0;
//   #100
//   btnL=1;
//   #200
//   Lborder=1;
//   btnL=0;
   
   //go down
   btnD=0;
   #100
   btnD=1;
   #500
   btnD=0;
  
   end
endmodule
