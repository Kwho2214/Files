`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/02/2023 10:38:43 AM
// Design Name: 
// Module Name: playerstate

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


module playerstate(
    input clk,
    input btnC,
    input btnD,
    input btnL,
    input btnR,
    input [15:0] x,
    input [15:0] y,
    input freeze,
    input game_over,
    output [15:0] leds,
    
    output aboveground,
    output player
    );
    
    wire [10:0] Lborder, Rborder, Gborder, grass_border;
    assign Lborder = 11'd8;
    assign Rborder = 11'd629;
    assign Gborder = 11'd471;
    assign grass_border = 11'd412;
    
    
    wire [6:1] ps, ns;
    FDRE #(.INIT(1'b1)) Q0_FF (.C(clk), .R(1'b0), .CE(1'b1), .D(ns[1]), .Q(ps[1]));  
    FDRE #(.INIT(1'b0)) Q4_FF[6:2] (.C({5{clk}}), .R({5{1'b0}}), .CE({5{1'b1}}), .D(ns[6:2]), .Q(ps[6:2]));
    
    wire [15:0] h_in, v_in, h_out, v_out;
    assign h_in = 16'b0;
    assign v_in = 16'b0;
    
    wire [15:0] playerbot, playerside;
    //players bottoms
    assign playerbot = 11'd412 + v_out;
    //players sides
    assign playerside = 11'd304 + h_out;
    assign player = (y >= playerbot - 16) & (y <= playerbot) & (x >= playerside - 16) & (x <= playerside);
    
    wire frame;
    assign frame = x == 700 & y == 500;
    //assign frame = 1;
    
    score_counter horizontal (.clk(clk), .Up(frame & ps[2] & ~ps[4] & ~ps[5]), .Dw(frame & ps[3] & ~ps[4] & ~ps[5]), .LD(1'b0), .reset(freeze & btnC), .enable(~freeze), .Din(h_in[15:0]), .Q(h_out[15:0]), .UTC(), .DTC());
    score_counter vertical (.clk(clk), .Up(frame & ps[4] & ~ps[2] & ~ps[3]), .Dw(frame & ps[5] & ~ps[2] & ~ps[3]), .LD(1'b0), .reset(freeze & btnC), .enable(~freeze), .Din(v_in[15:0]), .Q(v_out[15:0]), .UTC(), .DTC());
    
    wire g_limit, r_limit, l_limit, grass_lim;
    //1 when true       border == where u at
    assign g_limit = ~|(Gborder ^ playerbot);
    assign r_limit = ~|(Rborder ^ playerside);
    assign l_limit = ~|(Lborder ^ playerside - 16);
    assign leds[15] = l_limit;
    assign grass_lim = ~|(grass_border ^ playerbot);
    
    //start
    assign ns[1] = ps[1] | ps[1] & (~btnC & ~btnL & ~btnR & ~btnD);
    assign leds[1] = ps[1];
    //go right
    assign ns[2] = (ps[1] & (btnR & ~btnL & ~btnD & ~r_limit & ~ps[4] & ~ps[5]) | ps[2] & (btnR & ~btnL & ~btnD & ~r_limit & ~ps[4] & ~ps[5])) & aboveground;
    assign leds[2] = ps[2];
    //go left
    assign ns[3] = (ps[1] & (btnL & ~btnR & ~btnD & ~l_limit & ~ps[4] & ~ps[5]) | ps[3] & (btnL & ~btnR & ~btnD & ~l_limit & ~ps[4] & ~ps[5])) & aboveground;
    assign leds[3] = ps[3];
    //go down
    assign ns[4] = ps[1] & (btnD & ~btnR & ~btnL & ~g_limit) | ps[4] & (btnD & ~btnL & ~btnR & ~g_limit);
    assign leds[4] = ps[4];
    //go up
    assign ns[5] = ps[4] & (~btnD & ~btnL & ~btnR & ~grass_lim) | ps[5] & (~btnD & ~btnL & ~btnR & ~grass_lim) | ps[6] & (~btnD & ~btnL & ~btnR & ~grass_lim);
    //stop b/c reach borders\
    assign ns[6] = ps[2] & (r_limit & ~l_limit & ~g_limit) | ps[3] & (l_limit & ~r_limit & ~g_limit) | ps[4] & (g_limit & ~r_limit & ~l_limit) | ps[5] & (grass_lim & ~l_limit & ~g_limit & ~r_limit) | ps[6];
    assign leds[6] = ps[6];
    
    assign aboveground = grass_lim;
   
    
endmodule
