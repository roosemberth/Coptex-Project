/*
 * 
 * 
 * Acronims:
 * 	OD		= Outer Diameter		ID		= Inner Diameter	M		= Metric			Num		= Number
 *	GArea	= Gear Area				Max		= Maximum			Min		= Minimum			Spec	= Specification
 *	MSL		= Magnet Shield Lock	LHO		= Lock Hole Offset	MSLHO	= MSL Hole Offset	MSLW	= Magnet Shield Lock Width
 *	MTD		= M Thread Diameter		MTL		= M Thread Lenght	MTH		= M Thread Head				= 					
 */

//include <Swash Plate Modules.scad>;

$render=1;

$fn=64;										//+ Precision
mm=1;										//+ Milimeter size in mm (D̶u̶h̶!̶ ̶x̶D̶ Useful for Scaling!)
in=25.4*mm;									//+ Inch Size in mm
MinWall=1*mm;								//+ Minimum Wall Thickness in mm
Magnet=[5/4*in, 1/2*in, 1.5/16*in];			//+ Magnet Dimensions:			[OD, ID, Height]
MagnetShield=[10*mm, 3*mm, 6];				//+ Magnet Shield Dimensions:	[MSLHO, MSLW, Magnet Shield Crown Supports]
GArea=[Magnet[1], 25*mm, 8];				//+ Gear Area Dimensions:		[Max OD, Height, Num of Faces]
Gear=[10*mm, 10];							//+ Gear Dimensions:			[OD, Num of Teeth]
Mast=[GArea[0]*cos(180/GArea[2]), 40*mm];	//+ Main Mast Dimensions:		[Mast OD, Height]
Bolt1=["M2", 2*mm, 6*mm, 2*mm, 3*mm, 6];	//+ Bolt Set 1 Dimensions:		[M Spec, MTD, MTL, MTH Height, MTH Diameter, MTH Faces]
Nut1=["M2", Bolt1[3], Bolt1[4], Bolt1[5]];	//+ Nut Set 1 Dimensions:		[M Spec, Nut Height, Nut Diameter, Nut Faces]
Faster1=["M2", Bolt1, Nut1];				//+ Faster Set (Bolt and Nut)	[M Spec, Bolt Array, Nut Array]

rotate([0,0,0]) mast_holder(magnet=0);  																		// CP: make me
mast();  																										// CP: make me
magnet_shield(MagnetShield=[0,MagnetShield[1]], Model=2, $render=0){mast();};									// CP: make me
/*magnet();																										// CP: make me*/

/*square(50, center=true);*/
/*rotate([90,0,0]) square(50, center=true);*/
/*magnet_shield(Magnet=[240, 10, 100], Lock=0, $render=0);*/

/////////////////////////////////////////////////////////////////////////////////////////////////+ Magnetic Suspension System Modules

module bolt(Bolt=Bolt1){
	cylinder(h=Bolt[2], r=Bolt[1]/2, center=true);
	translate([0,0,(Bolt[2]+Bolt[3])/2]) cylinder(h=Bolt[3], center=true, $fn=Bolt[5]==0?$fn:Bolt[5], r=Bolt[4]/2);
}

module nut(Nut=Nut1){
	cylinder(h=Bolt[2], r=Bolt[1]/2, center=true);
	translate([0,0,(Bolt[2]+Bolt[3])/2]) cylinder(h=Bolt[3], center=true, $fn=Bolt[5]==0?$fn:Bolt[5], r=Bolt[4]/2);
}

module magnet(Magnet=Magnet){
	difference(){
		union(){
			color("Blue") translate([0,0,-(Magnet[2]/4)]) cylinder(r=Magnet[0]/2, h=(Magnet[2]/2), center=true);
			color("Red")  translate([0,0,+(Magnet[2]/4)]) cylinder(r=Magnet[0]/2, h=(Magnet[2]/2), center=true);
		}
		cylinder(r=Magnet[1]/2, h=Magnet[2]+1, center=true);
	}
}

module magnet_shield(Magnet=Magnet, Wall=MinWall, Lock=1, Fasters=Faster1, Nuts=Nut1, MagnetShield=MagnetShield, Model=1, Crown=5){
	Bolts=Fasters[1];
	LHO=Magnet[0]*0.5+Wall+Bolts[1]+MagnetShield[0];
	SIZE=[2*(LHO+2+Bolts[1]), 2*(LHO+2+Bolts[1]), max(Magnet[2]+2*Wall, max(2*Bolts[1], 2*Crown))];
	for(a=[0:($render)]) rotate([0,0,a*180]) color("Gray") render() difference(){
		union(){
			difference(){
				union(){
					magnet([Magnet[0]+2*Wall, Magnet[1]/2, Magnet[2]+2*Wall]);
					if (Lock!=0){
						difference(){
							union(){
								if (Model==2){
									rotate([(Model%2)*90,0,90]) hull(){
										translate([-LHO,0,0]) cylinder(r=Bolts[1], h=(MagnetShield[1]+(Model+1)%2), center=true);
										translate([+LHO,0,0]) cylinder(r=Bolts[1], h=(MagnetShield[1]+(Model+1)%2), center=true);
									}
									rotate([(Model%2)*90,0,00]) hull(){
										translate([-LHO,0,0]) cylinder(r=Bolts[1], h=(MagnetShield[1]+(Model+1)%2), center=true);
										translate([+LHO,0,0]) cylinder(r=Bolts[1], h=(MagnetShield[1]+(Model+1)%2), center=true);
									}
								}
								for(i=[0:360/MagnetShield[2]:360]){
									rotate([90,0,i]) cylinder(r1=0, r2=Crown, h=LHO);
								}
								if (Model==3){
									rotate_extrude() translate([LHO,0,0]) circle(r=Crown, center=true);
								}
							}
						}
					}
				}
				if($children==0){
					cylinder(r=Magnet[0]/2-5*Wall, h=max(Magnet[2]+2*Wall, 2*Bolts[1])*1.1, center=true);
				} else {
					for (i = [0 : $children-1]) child(i);
					echo(str("Magnet Shield: Custom Inner Cutter found!"));
				}
				cylinder(r=Magnet[0]/2, h=(Magnet[2]), center=true);
				translate([((Model)%2)*2*SIZE[0]/2,0,-((Model+1)%2)*1.01*SIZE[2]/2]){
					cube([2*SIZE[0],2*SIZE[1],1.01*SIZE[2]], center=true);
				}
				translate([0,+LHO,0]){
					cylinder(r=max(Crown/2, Bolts[4]/2+1), h=MagnetShield[1], center=true);
				}
				translate([0,-LHO,0]){
					cylinder(r=max(Crown/2, Bolts[4]/2+1), h=MagnetShield[1], center=true);
				}
			}
			if (Model==3){
				translate([0,+LHO,+MagnetShield[1]/4]) cylinder(r=max(Crown/2, Bolts[4]/2+1), h=MagnetShield[1]/2, center=true);
				translate([0,-LHO,-MagnetShield[1]/4]) cylinder(r=max(Crown/2, Bolts[4]/2+1), h=MagnetShield[1]/2, center=true);
			}
		}
		if (Model==3){
			translate([0,+LHO,]){
				translate([0,0,-Nuts[1]/2]) rotate([000,0,0]) bolt(Bolt=[Bolts[0], Bolts[1], Bolts[2], Crown, Bolts[4], 0]);
				translate([0,0,+Nuts[1]/2]) rotate([180,0,0]) bolt(Bolt=[Bolts[0], Bolts[1], Bolts[2], Crown, Bolts[4], Bolts[5]]);
			}
			translate([0,-LHO,0]){
				translate([0,0,-Nuts[1]/2]) rotate([000,0,0]) bolt(Bolt=[Bolts[0], Bolts[1], Bolts[2], Crown, Bolts[4], 0]);
				translate([0,0,+Nuts[1]/2]) rotate([180,0,0]) bolt(Bolt=[Bolts[0], Bolts[1], Bolts[2], Crown, Bolts[4], Bolts[5]]);
			}
		}
	}
}

module mast(Mast=Mast, GArea=GArea){
	color("Gray") render() union(){
		cylinder(r=Mast[0]/2, h=Mast[1], center=true);
		cylinder(r=GArea[0]/2, h=GArea[1], center=true, $fn=GArea[2]);
		rotate([360,0,0]) translate([0,0,GArea[1]/2]) cylinder(h=0.01*Mast[1], r1=GArea[0]/2, r2=Mast[0]/2);
		rotate([180,0,0]) translate([0,0,GArea[1]/2]) cylinder(h=0.01*Mast[1], r1=GArea[0]/2, r2=Mast[0]/2);
	}
}

module raw_mast_holder_legs(Height=(GArea[1]-Magnet[2]), Thick=(MagnetShield[1]+MinWall)/2, Wall=MinWall, Fasters=Faster1){
	Bolts=Fasters[1];
	difference(){
		union(){
			hull(){
				translate([0,0,+Height/2]) sphere(r=Thick,center=true);
				translate([0,0,-Height/2]) sphere(r=Thick,center=true);
			}
			translate([0,0,+Height/2]) sphere(r=Thick+Wall,center=true);
			translate([0,0,-Height/2]) sphere(r=Thick+Wall,center=true);
		}
		for(a=[-1:2:1]){
			translate([0,0,a*Height/2]){
				rotate([90,0,0]) cylinder(r=Bolts[1]/2,h=2*(Bolts[1]+Wall+1),center=true);
			}
			translate([0,0,a*Height/2]) rotate([90,0,0]) hull(){
				translate([Bolts[1]+Wall,0,0]) cylinder(r=Bolts[1], h=MagnetShield[1], center=true);
				cylinder(r=Bolts[1], h=MagnetShield[1], center=true);
			}
		}
	}
}

module mast_holder(Height=GArea[1]-Magnet[2], Magnet=Magnet, Wall=MinWall, Bolts=Bolt1, magnet=$render, MagnetShield=MagnetShield){
	color("Gray") render() for(i=[0:$render*4]){
//		rotate([0,0,i*90+180]) translate([-$render*(Magnet[0]*0.5+Wall+Bolt1[1]+MagnetShield[0]),0,0]) raw_mast_holder_legs();
	}
	for(a=[-1:2:$render%2]){
		translate([0,0,$render*a*Height/2]){
			magnet_shield(Lock=1, $render=0, Model=3);
		}
	}
	if($render&&(magnet==1)){
		rotate([180,0,0]) translate([0,0,-(GArea[1]-Magnet[2])/2]) magnet();
		rotate([180,0,0]) translate([0,0,+(GArea[1]-Magnet[2])/2]) magnet();
	}
}
