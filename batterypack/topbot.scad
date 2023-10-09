module one(x,y){
    difference(){
        translate([0,0,15/2])cube([20,20,15],center=true);

        translate([0,0,15/2+1])cylinder(15, r=9.4,center=true,$fn=50);
        translate([0,0,0])cylinder(100, r=2.5,center=true,$fn=50);

        translate([+10,+10,0])cylinder(66, r=3,center=true,$fn=50);
        translate([-10,-10,0])cylinder(66, r=3,center=true,$fn=50);
        translate([-10,+10,0])cylinder(66, r=3,center=true,$fn=50);
        translate([+10,-10,0])cylinder(66, r=3,center=true,$fn=50);

        rotate([0,0,45])translate([19,0,1])cube([20,5.4,2.01],center=true);
        rotate([0,0,135])translate([19,0,1])cube([20,5.4,2.01],center=true);
        rotate([0,0,225])translate([19,0,1])cube([20,5.4,2.01],center=true);
        rotate([0,0,315])translate([19,0,1])cube([20,5.4,2.01],center=true);
/*
        translate([0,0,2.0-0.3])cylinder(0.61, r=4,center=true,$fn=50);
        translate([0,0,0.8+0.3])cylinder(0.61, r=5,center=true,$fn=50);

        union(){
            rotate([0,0,45])translate([10,0,0.4])cube([20,5,0.81],center=true);
            rotate([0,0,-45])translate([0.0,0.0,0.4])cube([19,19,0.81],center=true);
        }
*/
    }
    translate([0,-9.75,0.5])cube([10,0.5,1],center=true);
    translate([0, 9.75,0.5])cube([10,0.5,1],center=true);
    translate([-9.75,0,0.5])cube([0.5,10,1],center=true);
    translate([ 9.75,0,0.5])cube([0.5,10,1],center=true);
}

translate([10,10,0])rotate([0,0,-90])one();
translate([30,10,0])rotate([0,0,-90])one();
/*
translate([50,10,0])rotate([0,0,-90])one();
translate([70,10,0])rotate([0,0,-90])one();
translate([90,10,0])rotate([0,0,-90])one();
translate([110,10,0])rotate([0,0,-90])one();
*/
translate([10,30,0])rotate([0,0,-90])one();
translate([30,30,0])rotate([0,0,-90])one();
/*
translate([50,30,0])rotate([0,0,-90])one();
translate([70,30,0])rotate([0,0,-90])one();
translate([90,30,0])rotate([0,0,-90])one();
translate([110,30,0])rotate([0,0,-90])one();

translate([10,50,0])rotate([0,0,-90])one();
translate([30,50,0])rotate([0,0,-90])one();
translate([50,50,0])rotate([0,0,-90])one();
translate([70,50,0])rotate([0,0,-90])one();
translate([90,50,0])rotate([0,0,-90])one();
translate([110,50,0])rotate([0,0,-90])one();

translate([10,70,0])one();
translate([30,70,0])one();
translate([50,70,0])one();
translate([70,70,0])one();
translate([90,70,0])one();
translate([110,70,0])one();

translate([10,90,0])one();
translate([30,90,0])one();
translate([50,90,0])one();
translate([70,90,0])one();
translate([90,90,0])one();
translate([110,90,0])one();

translate([10,110,0])one();
translate([30,110,0])one();
translate([50,110,0])one();
translate([70,110,0])one();
translate([90,110,0])one();
translate([110,110,0])one();
*/