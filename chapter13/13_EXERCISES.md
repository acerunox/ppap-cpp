## Drill
1. Make an 800-by-1000 Simple_window.
1. Put an 8-by-8 grid on the leftmost 800-by-800 part of that window (so that each square is 100 by 100).
1. Make the eight squares on the diagonal starting from the top left corner red (use Rectangle).
1. Find a 200-by-200-pixel image (JPEG or GIF) and place three copies of it on the grid (each image covering four squares). If you can’t find an image that is exactly 200 by 200, use set_mask() to pick a 200-by-200 section of a larger image. Don’t obscure the red squares.
1. Add a 100-by-100 image. Have it move around from square to square when you click the “Next” button. Just put wait_for_button() in a loop with some code that picks a new square for your image.

## Exercise 01
1. Define a class Arc, which draws a part of an ellipse. Hint: fl_arc().

## Exercise 02
1. Draw a box with rounded corners.
1. Define a class Box, consisting of four lines and four arcs.