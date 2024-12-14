`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/06/2023 04:13:41 PM
// Design Name: 
// Module Name: ship
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


module ship(
    input clk,
    input btnC,
    input [15:0] x,
    input [15:0] y,
    input player,
    input infreeze,
    input game_over,
    output ship,
    output slug,
    output showship, showslug,
    output outfreeze,
    output flashborder,
    output flashplayer,
    output flashslug,
    output outgo,
    output point,
    output [15:0] ship_side,
    output [15:0] led
    );
    
    //frame signal
    wire frame;
    assign frame = (x == 700 & y == 500) | (x == 350 & y == 250);
    //assign frame = 1;
    
    wire [10:0] grass_border;
    wire ground;
    assign grass_border = 11'd411;
    
    wire contact, resettime, slugcontact, edgeout;
    wire [15:0] time_out;
//    time_counter time1 (.clk(clk), .Up(frame), .Dw(1'b0), .Din(t_in), .Q(t_out), .R(ps[1] & ground));
    score_counter total_time (.clk(clk), .enable(1'b1), .reset(resettime), .Up(frame), .Dw(1'b0), .Din(16'b0), .LD(1'b0), .Q(time_out), .UTC(), .DTC());
    
    wire t1, t3, tf;
    assign t1 = time_out[5] & time_out[4] & time_out[3] & time_out[2] & ~time_out[1] & ~time_out[0];
    assign t3 = time_out[7] & ~time_out[6] & time_out[5] & time_out[4] & ~time_out[3] & time_out[2] & ~time_out[1] & ~time_out[0];
    assign tf = time_out[9] & time_out[8] & ~time_out[7] & ~time_out[6] & ~time_out[5] & ~time_out[4] & ~time_out[3] & ~time_out[2] & ~time_out[1] & ~time_out[0];
    
    Edge_dect edgego (.clk(clk), .x(ps[1]), .Z(edgeout));
    wire [15:0] rand; 
    rand_num random_num (.clkin(clk), .Q(rand));
    wire [15:0] hold;
    //ps[4] | (ps[5] & btnC)
    FDRE #(.INIT(1'b0)) rand0 (.C(clk), .R(ps[6] | (game_over)), .CE(edgeout), .D(rand[0]), .Q(hold[0]));
    FDRE #(.INIT(1'b0)) rand1[15:1] (.C({15{clk}}), .R({15{(ps[6] | (game_over))}}), .CE({15{(edgeout)}}), .D(rand[15:1]), .Q(hold[15:1])); 
    
    wire [15:0] v_in, v_out;
    wire [15:0] ship_bot;
    assign v_in = 16'b0;
    score_counter vertical (.clk(clk), .Up(frame & ps[1]), .Dw(1'b0), .LD(1'b0), .reset((ps[6]) | game_over), .enable(~infreeze), .Din(v_in[15:0]), .Q(v_out[15:0]), .UTC(), .DTC());
    
    assign ground = ~|(grass_border ^ ship_bot);
    
    wire [6:0] ps, ns;
    FDRE #(.INIT(1'b1)) Q0_FF (.C(clk), .R(1'b0), .CE(1'b1), .D(ns[0]), .Q(ps[0]));  
    FDRE #(.INIT(1'b0)) Q3_FF[6:1] (.C({6{clk}}), .R({6{1'b0}}), .CE({6{1'b1}}), .D(ns[6:1]), .Q(ps[6:1]));
    
    assign contact = (player & ship & showship);
    
    
    //idle
    assign ns[0] = ps[0] & ~btnC | ps[5] & (~btnC & (~contact | ~infreeze));
    assign led[0] = ps[0];
    //start falling
    assign ns[1] = ps[0] & (btnC) | ps[1] & (~ground & (~contact & ~infreeze)) | ps[6] | (ps[4] & t1);
    assign outgo = ps[1];
    assign led[1] = ps[1];
    //stop at ground lvl
    assign ns[2] = ps[1] & (ground & (~contact & ~infreeze)) | ps[2] & ~t1;
    assign led[2] = ps[2];
    //delete ship
    assign ns[3] = (ps[2] & t1 & ~contact) | ps[3] & (~t3 & ~contact);
    assign led[3] = ps[3];
    //only alien slug on ground and player touch
    assign ns[4] = ps[3] & (~t3 & player & slug) | (ps[4] & ~t1);
    assign point = ps[3] & (~t3 & player & slug & showslug);
    assign led[4] = ps[4];
    //not touch player
    assign ns[6] =  ps[3] & t3;
    assign led[6] = ps[6];
    //make freeze
    assign ns[5] = ps[1] & (contact | infreeze) | ps[2] & (contact | infreeze) | ps[5] & (~btnC & (contact)) | ps[3] & (contact | infreeze) | ps[4] & (contact | infreeze);
    assign led[5] = ps[5];
    
    assign outfreeze = ps[5];
    assign showship = ps[1] | ps[2] ;
    assign showslug = ps[1] | ps[2] | ps[3] | ps[4] & ~t1;
    assign resettime = ps[1] & ground | ps[3] & t3 | ps[4] & t1;
  
    assign flashborder = time_out[5] & (game_over);
    assign flashplayer = time_out[4] & (game_over);
    assign flashslug = time_out[3] & game_over;
    
    
    
    
    
    
    
    
    
    
    //ship draw
    assign ship_bot =  v_out; //{15'b1,(~ps[4] & time1)}
    assign ship_side = ((hold[3:0] + 1) << 5);
    assign ship = ((y >= ship_bot - 10) & (y <= ship_bot) & (x >= ship_side) & (x <= ship_side + ((hold[2:1]+1)<< 5) & x < 640));
    
    //ship draw
    wire [15:0] slug_side, slug_bot;
    assign slug_bot =  v_out - 16'd2;
    //(hold[3:0] << 5) +
    assign slug_side =  (ship_side + (((hold[2:0]+1)<<5)>>2));
    assign slug = ((y >= slug_bot - 4) & (y <= slug_bot) & (x >= slug_side - 4) & (x <= slug_side));
     
endmodule
