`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/12/2023 02:45:00 PM
// Design Name: 
// Module Name: tar_sim
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


module tar_sim(

    );
    reg [3:0] Din;
    reg ce, clkin;
    wire [3:0] Q;
    
    target_num UUT(
    .Din(Din),
    .ce(ce),
    .clkin(clkin),
    .Q(Q)
    
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
    ce=1;
    Din = 1101;
    #500;
    Din=4'b0;
    #200
    ce=0;
    #200
    Din=4'b0011;
    #100
    ce=1;
    #50
    ce=0;
    
    
    end
endmodule
