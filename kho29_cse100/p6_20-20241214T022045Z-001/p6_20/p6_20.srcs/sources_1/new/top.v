`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/28/2023 10:56:32 AM
// Design Name: 
// Module Name: top
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


module top(
   input btnC,
   input btnD,
   input btnU,
   input btnL,
   input btnR,
   input [15:0] sw,
   input clkin,
   output [3:0] an,
   output dp,
   output [6:0] seg,
   output [15:0] led,
   output [3:0] vgaRed,
   output [3:0] vgaGreen,
   output [3:0] vgaBlue,
   output Vsync,
   output Hsync
   );
    
    wire clk, digsel;
    labVGA_clks not_so_slow (.clkin(clkin), .greset(btnU), .clk(clk), .digsel(digsel));
    
    wire [15:0] h, v, h_out, v_out, s_out;
    wire h_reset, v_reset;
    
    wire [9:0] h_max, v_max;
    wire playercoord;
    wire [4:0] ship_side, slug_in, shipcoord;
    wire frame;
    
    assign h_max = 10'd799;
    assign v_max = 10'd525;
    
    assign h_reset = ~|(h_out[9:0] ^ h_max);
    assign v_reset = ~|(v_out[9:0] ^ v_max);
    
    //prev up h_out^16'd799
    
    score_counter h_count (.clk(clk), .reset(h_reset), .enable(1'b1), .Up(1'b1), .Dw(1'b0), .Din(16'b0), .LD(h_reset), .Q(h_out), .UTC(), .DTC());
    score_counter v_count (.clk(clk), .reset(v_reset), .enable(1'b1), .Up(h_reset), .Dw(1'b0), .Din(16'b0), .LD(h_reset & v_reset), .Q(v_out), .UTC(), .DTC());
    assign frame = (h_out == 700 & v_out == 500);
    //assign frame = 1;
    
    //FDRE #(.INIT(1'b0)) sig (.C(clk), .R(1'b0), .CE(), .D(), .Q());
    
    vga vga_one (.clk(clk), .h(h_out), .v(v_out), .H_sync(Hsync), .V_sync(Vsync));
    
    wire [4:0] showship, showslug, outgo, outfreeze, infreeze, flashborder, flashplayer, flashslug, point;
    
    wire Go1, Go2, Go3, Go4, Go5, game_over;
    
    
    color color1(.y(v_out), .x(h_out), .r(vgaRed), .g(vgaGreen), .b(vgaBlue), .player_cord(playercoord), 
    
    .ship1(shipcoord[0]), .ship2(shipcoord[1]), .ship3(shipcoord[2]), .ship4(shipcoord[3]), .ship5(shipcoord[4]), 
    .slug1(slug_in[0]), .slug2(slug_in[1]), .slug3(slug_in[2]), .slug4(slug_in[3]), .slug5(slug_in[4]), 
    
    .showship1(showship[0]), .showship2(showship[1]), .showship3(showship[2]), .showship4(showship[3]), .showship5(showship[4]), 
    .showslug1(showslug[0]), .showslug2(showslug[1]), .showslug3(showslug[2]), .showslug4(showslug[3]), .showslug5(showslug[4]), 
    
    .flashplayer1(flashplayer[0]), .flashplayer2(flashplayer[1]), .flashplayer3(flashplayer[2]), .flashplayer4(flashplayer[3]), .flashplayer5(flashplayer[4]),
    .flashborder1(flashborder[0]), .flashborder2(flashborder[1]), .flashborder3(flashborder[2]), .flashborder4(flashborder[3]), .flashborder5(flashborder[4]),
    .flashslug1(flashslug[0]), .flashslug2(flashslug[1]), .flashslug3(flashslug[2]), .flashslug4(flashslug[3]), .flashslug5(flashslug[4]));
    
    
    wire [15:0] led_out;
    wire totalfreeze;
    assign totalfreeze = outfreeze[0] | outfreeze[1] | outfreeze[2] | outfreeze[3] | outfreeze[4];
    playerstate player (.clk(clk), .x(h_out), .y(v_out), .btnC(btnC), .btnD(btnD), .btnL(btnL), .btnR(btnR), .player(playercoord), .leds(led[15]), .freeze(totalfreeze), .game_over(game_over));
    
    game_state game (.clk(clk), .x(h_out), .y(v_out), .btnC(btnC), .freeze(totalfreeze), .Go1(Go1), .Go2(Go2), .Go3(Go3), .Go4(Go4), .Go5(Go5), .led(), .game_over(game_over));
    
    //ship1
    ship ship1 (.clk(clk), .btnC(Go1), .x(h_out), .y(v_out), .showship(showship[0]), .showslug(showslug[0]), .ship(shipcoord[0]), .slug(slug_in[0]), .player(playercoord), .ship_side(ship_side[0]), .infreeze(totalfreeze), .outfreeze(outfreeze[0]), .led(led), .flashplayer(flashborder[0]), .flashborder(flashplayer), .flashslug(flashslug[0]), .outgo(outgo[0]), .game_over(game_over), .point(point[0]));
    //sship2
    ship ship2 (.clk(clk), .btnC(Go2), .x(h_out), .y(v_out), .showship(showship[1]), .showslug(showslug[1]), .ship(shipcoord[1]), .slug(slug_in[1]), .player(playercoord), .ship_side(ship_side[1]), .infreeze(totalfreeze), .outfreeze(outfreeze[1]), .flashplayer(flashplayer[1]), .flashborder(flashborder[1]), .flashslug(flashslug[1]), .outgo(outgo[1]), .game_over(game_over), .point(point[1]));
    //ship3
    ship ship3 (.clk(clk), .btnC(Go3), .x(h_out), .y(v_out), .showship(showship[2]), .showslug(showslug[2]), .ship(shipcoord[2]), .slug(slug_in[2]), .player(playercoord), .ship_side(ship_side[2]), .infreeze(totalfreeze), .outfreeze(outfreeze[2]), .flashplayer(flashplayer[2]), .flashborder(flashborder[2]), .flashslug(flashslug[2]), .outgo(outgo[2]), .game_over(game_over), .point(point[2]));
    //ship4
    ship ship4 (.clk(clk), .btnC(Go4), .x(h_out), .y(v_out), .showship(showship[3]), .showslug(showslug[3]), .ship(shipcoord[3]), .slug(slug_in[3]), .player(playercoord), .ship_side(ship_side[3]), .infreeze(totalfreeze), .outfreeze(outfreeze[3]), .flashplayer(flashplayer[3]), .flashborder(flashborder[3]), .flashslug(flashslug[3]), .outgo(outgo[3]), .game_over(game_over), .point(point[3]));
    //ship5
    ship ship5 (.clk(clk), .btnC(Go5), .x(h_out), .y(v_out), .showship(showship[4]), .showslug(showslug[4]), .ship(shipcoord[4]), .slug(slug_in[4]), .player(playercoord), .ship_side(ship_side[4]), .infreeze(totalfreeze), .outfreeze(outfreeze[4]), .flashplayer(flashplayer[4]), .flashborder(flashborder[4]), .flashslug(flashslug[4]), .outgo(outgo[4]), .game_over(game_over), .point(point[4]));
    
    wire totalpoints, incscore;
//    assign totalpoints = (playercoord & slug_in[0]) | (playercoord & slug_in[1]) | (playercoord & slug_in[2]) | (playercoord & slug_in[3]) | (playercoord & slug_in[4]);
//    Edge_dect edgego (.clk(clk), .x(totalpoints), .Z(incscore));
    assign totalpoints = point[0] | point[1] | point[2] | point[3] | point[4];
    //Edge_dect edgeinc (.clk(clk), .x(totalpoints), .Z(incscore));
    
    score_counter score (.clk(clk), .reset(btnC), .enable(1'b1), .Up(totalpoints), .Dw(1'b0), .Din(16'b0), .LD(1'b0), .Q(s_out), .UTC(), .DTC());
    //ringcounter
    wire [3:0] ring_out;
    Ring_counter ring1 (.adv(digsel), .clk(clk), .out(ring_out[3:0]));
    
    //selector
    wire [3:0] sel_out;
    selector sel (.sel(ring_out[3:0]), .N(s_out), .H(sel_out[3:0]));
    
    //hex7seg
    wire [6:0] hex;
    hex7seg h1 (.n(sel_out[3:0]), .led(hex[6:0]));
    
    assign seg[6:0] = hex[6:0];
    assign an[3] = 1;
    assign an[2] = 1;
    assign an[1] = ~ring_out[1];
    assign an[0] = ~ring_out[0];
    assign dp = 1;
    
endmodule
