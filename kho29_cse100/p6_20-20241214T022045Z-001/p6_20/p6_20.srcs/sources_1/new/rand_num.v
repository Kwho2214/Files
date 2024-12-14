`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/07/2023 11:51:07 AM
// Design Name: 
// Module Name: rand_num
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


module rand_num(
    input clkin,
    output [15:0] Q
    );
    
    wire [15:0] rnd;
    
    FDRE #(.INIT(1'b1)) Q0_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[0]^rnd[5]^rnd[6]^rnd[7]),.Q(rnd[0]));
    FDRE #(.INIT(1'b0)) Q1_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[0]),.Q(rnd[1]));
    FDRE #(.INIT(1'b0)) Q2_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[1]),.Q(rnd[2]));  
    FDRE #(.INIT(1'b0)) Q3_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[2]),.Q(rnd[3]));
    FDRE #(.INIT(1'b0)) Q4_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[3]),.Q(rnd[4]));
    FDRE #(.INIT(1'b0)) Q5_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[4]),.Q(rnd[5]));
    FDRE #(.INIT(1'b0)) Q6_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[5]),.Q(rnd[6]));
    FDRE #(.INIT(1'b0)) Q7_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[6]),.Q(rnd[7]));
    FDRE #(.INIT(1'b0)) Q8_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[7]),.Q(rnd[8]));
    FDRE #(.INIT(1'b0)) Q9_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[8]),.Q(rnd[9]));  
    FDRE #(.INIT(1'b0)) Q10_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[9]),.Q(rnd[10]));
    FDRE #(.INIT(1'b0)) Q11_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[10]),.Q(rnd[11]));
    FDRE #(.INIT(1'b0)) Q12_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[11]),.Q(rnd[12]));
    FDRE #(.INIT(1'b0)) Q13_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[12]),.Q(rnd[13]));
    FDRE #(.INIT(1'b0)) Q14_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[13]),.Q(rnd[14]));
    FDRE #(.INIT(1'b0)) Q15_FF (.C(clkin),.R(1'b0),.CE(1'b1),.D(rnd[14]),.Q(rnd[15]));
    
    assign Q[15:0] = rnd[15:0];
endmodule
