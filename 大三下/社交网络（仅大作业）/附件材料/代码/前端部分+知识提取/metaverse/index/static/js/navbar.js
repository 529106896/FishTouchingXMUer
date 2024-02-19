$(document).ready(function() {
	
	// Navbar hiding
	var nav_container = $('.navbar-fixed-top');
	var top_spacing = 40;
	var waypoint_offset = 50;

	nav_container.waypoint({
		handler: function(event, direction) {
			if (direction == 'down') { // On scroll down hide if > waypoint_offset down
				nav_container.stop().addClass('navbar-hidden').animate({"top":-top_spacing});
			} else { 
				nav_container.stop().removeClass('navbar-hidden').animate({"top":"0"});
			}
			nav_container.hover(
				function () { // Show navbar if hover
					nav_container.stop().removeClass('navbar-hidden').animate({"top":"0"});
				},
				function () {
					nav_container.stop().addClass('navbar-hidden').animate({"top":-top_spacing});
				}
			);
		},
		offset: function() {
			return -nav_container.outerHeight()-waypoint_offset;
		}
	});
	
});
