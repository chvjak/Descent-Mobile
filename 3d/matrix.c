/*
THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.
COPYRIGHT 1993-1998 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
*/
/*
* $Source: Buggin:miner:source:3d::RCS:matrix.c $
* $Revision: 1.1 $
* $Author: allender $
* $Date: 1995/05/05 08:52:11 $
*
* Matrix setup & manipulation routines
*
* $Log: matrix.c $
* Revision 1.1  1995/05/05  08:52:11  allender
* Initial revision
*
* Revision 1.1  1995/04/17  04:14:34  matt
* Initial revision
*
*
*/


#pragma off (unreferenced)
static char rcsid[] = "$Id: matrix.c 1.1 1995/05/05 08:52:11 allender Exp $";
#pragma on (unreferenced)

#include <string.h>
#include "globvars.h"
#include "3d.h"

void scale_matrix(void);

//set view from x,y,z & p,b,h, zoom.  Must call one of g3_set_view_*() 
void g3_set_view_angles(vms_vector *view_pos, vms_angvec *view_orient, fix zoom) {
	View_zoom = zoom;
	View_position = *view_pos;

	vm_angles_2_matrix(&View_matrix, view_orient);

	scale_matrix();

}

//set view from x,y,z, viewer matrix, and zoom.  Must call one of g3_set_view_*() 
void g3_set_view_matrix(vms_vector *view_pos, vms_matrix *view_matrix, fix zoom) {
	View_zoom = zoom;

	View_position.x = view_pos->x;
	View_position.y = view_pos->y;
	View_position.z = view_pos->z;

	memcpy(&View_matrix, view_matrix, sizeof(vms_matrix));

	scale_matrix();
}

//performs aspect scaling on global view matrix
void scale_matrix(void) {
	Unscaled_matrix = View_matrix;		//so we can use unscaled if we want

	Matrix_scale = Window_scale;

	if (View_zoom <= f1_0) 		//zoom in by scaling z

		Matrix_scale.z = fixmul(Matrix_scale.z, View_zoom);

	else {			//zoom out by scaling x&y

		fix s = fixdiv(f1_0, View_zoom);

		Matrix_scale.x = fixmul(Matrix_scale.x, s);
		Matrix_scale.y = fixmul(Matrix_scale.y, s);
	}

	//now scale matrix elements

	vm_vec_scale(&View_matrix.rvec, Matrix_scale.x);
	vm_vec_scale(&View_matrix.uvec, Matrix_scale.y);
	vm_vec_scale(&View_matrix.fvec, Matrix_scale.z);

}
