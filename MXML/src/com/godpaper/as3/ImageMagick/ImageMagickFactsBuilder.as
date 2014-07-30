/**
 *  GODPAPER Confidential,Copyright 2012. All rights reserved.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sub-license,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included
 *  in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 */
package com.godpaper.as3.ImageMagick
{
	//--------------------------------------------------------------------------
	//
	// Imports
	//
	//--------------------------------------------------------------------------
	
	/**
	 * ImageMagickFactsBuilder.as class. 
	 * @author yangboz
	 * @langVersion 3.0
	 * @playerVersion 11.2+
	 * @airVersion 3.2+
	 * Created Jan 17, 2014 11:15:55 AM
	 * @history 12/30/13,
	 * @see http://www.imagemagick.org/script/convert.php#options
	 * @see http://www.imagemagick.org/Usage/
	 */ 
	public class ImageMagickFactsBuilder implements IImageMagickOptions
	{ 
		//--------------------------------------------------------------------------
		//
		// Variables
		//
		//--------------------------------------------------------------------------
		
		//----------------------------------
		// CONSTANTS
		//----------------------------------
		
		//--------------------------------------------------------------------------
		//
		// Public properties
		//
		//--------------------------------------------------------------------------
		
		//--------------------------------------------------------------------------
		//
		// Protected properties
		//
		//--------------------------------------------------------------------------
		
		
		//--------------------------------------------------------------------------
		//
		// Constructor
		//
		//--------------------------------------------------------------------------
		/**
		 * Constructure the ImageMagick CMD option with basic parameters 
		 * @param srcFile the file path for input
		 * @param desFile the file path for output
		 * 
		 */		
		public function ImageMagickFactsBuilder(srcFile:String,desFile:String)
		{
			//@required basic parameters.
			ImageMagickParameters.desFile = desFile;
			ImageMagickParameters.srcFile = srcFile;
		} 
		//--------------------------------------------------------------------------
		//
		// Public methods
		//
		//--------------------------------------------------------------------------
		//
		public function build():ImageMagickFacts
		{
			return new ImageMagickFacts(this);
		}
		//list: http://www.imagemagick.org/script/convert.php#options
		//
		//		-adaptive-blur geometry	adaptively blur pixels; decrease effect near edges
		//		-adaptive-resize geometry	adaptively resize image with data dependent triangulation.
		//			-adaptive-sharpen geometry	adaptively sharpen pixels; increase effect near edges
		//		-adjoin	join images into a single multi-image file
		//		-affine matrix	affine transform matrix
		//		-alpha	on, activate, off, deactivate, set, opaque, copy", transparent, extract, background, or shape the alpha channel
		//		-annotate geometry text	annotate the image with text
		//		-antialias	remove pixel-aliasing
		//			-append	append an image sequence
		//		-authenticate value	decipher image with this password
		//		-auto-gamma	automagically adjust gamma level of image
		//		-auto-level	automagically adjust color levels of image
		//		-auto-orient	automagically orient image
		//		-background color	background color
		//		-bench iterations	measure performance
		//		-bias value	add bias when convolving an image
		//		-black-threshold value	force all pixels below the threshold into black
		//		-blue-primary point	chromaticity blue primary point
		//		-blue-shift factor	simulate a scene at nighttime in the moonlight
		//		-blur geometry	reduce image noise and reduce detail levels
		//		-border geometry	surround image with a border of color
		//		-bordercolor color	border color
		//		-brightness-contrast geometry	improve brightness / contrast of the image
		//		-caption string	assign a caption to an image
		//		-cdl filename	color correct with a color decision list
		//		-channel type	apply option to select image channels
		//		-charcoal radius	simulate a charcoal drawing
		//		-chop geometry	remove pixels from the image interior
		//		-clamp	set each pixel whose value is below zero to zero and any the pixel whose value is above the quantum range to the quantum range (e.g. 65535) otherwise the pixel value remains unchanged.
		//			-clip	clip along the first path from the 8BIM profile
		//		-clip-mask filename	associate clip mask with the image
		//		-clip-path id	clip along a named path from the 8BIM profile
		//		-clone index	clone an image
		//		-clut	apply a color lookup table to the image
		//		-contrast-stretch geometry	improve the contrast in an image by `stretching' the range of intensity value
		//		-coalesce	merge a sequence of images
		//		-colorize value	colorize the image with the fill color
		//		-color-matrix matrix	apply color correction to the image.
		//			-colors value	preferred number of colors in the image
		//		-colorspace type	set image colorspace
		//		-combine	combine a sequence of images
		//		-comment string	annotate image with comment
		//		-compare	compare image
		//		-complexoperator	perform complex mathematics on an image sequence
		//		-compose operator	set image composite operator
		//		-composite	composite image
		//		-compress type	image compression type
		//		-contrast	enhance or reduce the image contrast
		//		-convolve coefficients	apply a convolution kernel to the image
		//		-crop geometry	crop the image
		//		-cycle amount	cycle the image colormap
		//		-decipher filename	convert cipher pixels to plain
		//		-debug events	display copious debugging information
		//		-define format:option	define one or more image format options
		//		-deconstruct	break down an image sequence into constituent parts
		//		-delay value	display the next image after pausing
		//		-delete index	delete the image from the image sequence
		//		-density geometry	horizontal and vertical density of the image
		//		-depth value	image depth
		//		-despeckle	reduce the speckles within an image
		//		-direction type	render text right-to-left or left-to-right
		//			-display server	get image or font from this X server
		//		-dispose method	layer disposal method
		//		-distribute-cache port	launch a distributed pixel cache server
		//		-distort type coefficients	distort image
		//		-dither method	apply error diffusion to image
		//		-draw string	annotate the image with a graphic primitive
		//		-duplicate count,indexes	duplicate an image one or more times
		//		-edge radius	apply a filter to detect edges in the image
		//		-emboss radius	emboss an image
		//		-encipher filename	convert plain pixels to cipher pixels
		//		-encoding type	text encoding type
		//		-endian type	endianness (MSB or LSB) of the image
		//		-enhance	apply a digital filter to enhance a noisy image
		//		-equalize	perform histogram equalization to an image
		//		-evaluate operator value	evaluate an arithmetic, relational, or logical expression
		//		-evaluate-sequence operator	evaluate an arithmetic, relational, or logical expression for an image sequence
		//		-extent geometry	set the image size
		//		-extract geometry	extract area from image
		//		-family name	render text with this font family
		//		-features distance	analyze image features (e.g. contract, correlations, etc.).
		//			-fft	implments the discrete Fourier transform (DFT)
		//		-fill color	color to use when filling a graphic primitive
		//		-filter type	use this filter when resizing an image
		//		-flatten	flatten a sequence of images
		//		-flip	flip image in the vertical direction
		//		-floodfill geometry color	floodfill the image with color
		//		-flop	flop image in the horizontal direction
		//		-font name	render text with this font
		//		-format string	output formatted image characteristics
		//		-frame geometry	surround image with an ornamental border
		//		-function name	apply a function to the image
		//			-fuzz distance	colors within this distance are considered equal
		//			-fx expression	apply mathematical expression to an image channel(s)
		//			-gamma value	level of gamma correction
		//		-gaussian-blur geometry	reduce image noise and reduce detail levels
		//		-geometry geometry	preferred size or location of the image
		//		-gravity type	horizontal and vertical text placement
		//		-grayscale method	convert image to grayscale
		//		-green-primary point	chromaticity green primary point
		//		-help	print program options
		//		-identify	identify the format and characteristics of the image
		//		-ift	implements the inverse discrete Fourier transform (DFT)
		//		-implode amount	implode image pixels about the center
		//		-insert index	insert last image into the image sequence
		//		-intensity method	method to generate an intensity value from a pixel
		//		-intent type	type of rendering intent when managing the image color
		//		-interlace type	type of image interlacing scheme
		//		-interline-spacing value	the space between two text lines
		//		-interpolate method	pixel color interpolation method
		//		-interword-spacing value	the space between two words
		//		-kerning value	the space between two characters
		//		-label string	assign a label to an image
		//		-lat geometry	local adaptive thresholding
		//		-layers method	optimize or compare image layers
		//		-level value	adjust the level of image contrast
		//		-limit type value	pixel cache resource limit
		//		-linear-stretch geometry	linear with saturation histogram stretch
		//		-liquid-rescale geometry	rescale image with seam-carving
		//			-list type	Color, Configure, Delegate, Format, Magic, Module, Resource, or Type
		//		-log format	format of debugging information
		//		-loop iterations	add Netscape loop extension to your GIF animation
		//		-mask filename	associate a mask with the image
		//		-mattecolor color	frame color
		//		-median radius	apply a median filter to the image
		//		-metric type	measure differences between images with this metric
		//		-mode radius	make each pixel the 'predominant color' of the neighborhood
		//		-modulate value	vary the brightness, saturation, and hue
		//		-moments	display image moments.
		//			-monitor	monitor progress
		//		-monochrome	transform image to black and white
		//		-morph value	morph an image sequence
		//		-morphology method kernel	apply a morphology method to the image
		//		-motion-blur geometry	simulate motion blur
		//		-negate	replace each pixel with its complementary color
		//		-noise radius	add or reduce noise in an image
		//		-normalize	transform image to span the full range of colors
		//		-opaque color	change this color to the fill color
		//		-ordered-dither NxN	ordered dither the image
		//		-orient type	image orientation
		//		-page geometry	size and location of an image canvas (setting)
		//		-paint radius	simulate an oil painting
		//		-perceptible	set each pixel whose value is less than |epsilon| to -epsilon or epsilon (whichever is closer) otherwise the pixel value remains unchanged.
		//			-ping	efficiently determine image attributes
		//		-pointsize value	font point size
		//		-polaroid angle	simulate a Polaroid picture
		//		-poly terms	build a polynomial from the image sequence and the corresponding terms (coefficients and degree pairs).
		//			-posterize levels	reduce the image to a limited number of color levels
		//		-precision value	set the maximum number of significant digits to be printed
		//		-preview type	image preview type
		//		-print string	interpret string and print to console
		//		-process image-filter	process the image with a custom image filter
		//		-profile filename	add, delete, or apply an image profile
		//		-quality value	JPEG/MIFF/PNG compression level
		//		-quantize colorspace	reduce image colors in this colorspace
		//		-quiet	suppress all warning messages
		//		-radial-blur angle	radial blur the image
		//		-raise value	lighten/darken image edges to create a 3-D effect
		//		-random-threshold low,high	random threshold the image
		//		-red-primary point	chromaticity red primary point
		//		-regard-warnings	pay attention to warning messages.
		//			-region geometry	apply options to a portion of the image
		//		-remap filename	transform image colors to match this set of colors
		//		-render	render vector graphics
		//		-repage geometry	size and location of an image canvas
		//		-resample geometry	change the resolution of an image
		//		-resize geometry	resize the image
		//Convert
		/**
		 * 
		 * @param args command arguments string
		 * @see http://www.imagemagick.org/script/convert.php#options 
		 * @see http://www.imagemagick.org/script/montage.php
		 * @return ImageMagickFactsBuilder
		 * 
		 */		
		public function with_command(args:String):ImageMagickFactsBuilder
		{
			ImageMagickParameters.commandOpt = args;
			return this;
		}
		//		-respect-parentheses	settings remain in effect until parenthesis boundary.
		//			-roll geometry	roll an image vertically or horizontally
		//		-rotate degrees	apply Paeth rotation to the image
		//		-sample geometry	scale image with pixel sampling
		//		-sampling-factor geometry	horizontal and vertical sampling factor
		//		-scale geometry	scale the image
		//		-scene value	image scene number
		//		-seed value	seed a new sequence of pseudo-random numbers
		//		-segment values	segment an image
		//		-selective-blur geometry	selectively blur pixels within a contrast threshold
		//		-separate	separate an image channel into a grayscale image
		//		-sepia-tone threshold	simulate a sepia-toned photo
		//		-set attribute value	set an image attribute
		//		-shade degrees	shade the image using a distant light source
		//		-shadow geometry	simulate an image shadow
		//		-sharpen geometry	sharpen the image
		//		-shave geometry	shave pixels from the image edges
		//		-shear geometry	slide one edge of the image along the X or Y axis
		//		-sigmoidal-contrast geometry	increase the contrast without saturating highlights or shadows
		//		-smush offset	smush an image sequence together
		//		-size geometry	width and height of image
		//		-sketch geometry	simulate a pencil sketch
		//		-solarize threshold	negate all pixels above the threshold level
		//		-splice geometry	splice the background color into the image
		//		-spread radius	displace image pixels by a random amount
		//		-statistic type geometry	replace each pixel with corresponding statistic from the neighborhood
		//		-strip	strip image of all profiles and comments
		//		-stroke color	graphic primitive stroke color
		//		-strokewidth value	graphic primitive stroke width
		//		-stretch type	render text with this font stretch
		//		-style type	render text with this font style
		//		-swap indexes	swap two images in the image sequence
		//		-swirl degrees	swirl image pixels about the center
		//		-synchronize	synchronize image to storage device
		//		-taint	mark the image as modified
		//		-texture filename	name of texture to tile onto the image background
		//		-threshold value	threshold the image
		//		-thumbnail geometry	create a thumbnail of the image
		//		-tile filename	tile image when filling a graphic primitive
		//		-tile-offset geometry	set the image tile offset
		//		-tint value	tint the image with the fill color
		//		-transform	affine transform image
		//		-transparent color	make this color transparent within the image
		//		-transparent-color color	transparent color
		//		-transpose	flip image in the vertical direction and rotate 90 degrees
		//		-transverse	flop image in the horizontal direction and rotate 270 degrees
		//		-treedepth value	color tree depth
		//		-trim	trim image edges
		//		-type type	image type
		//		-undercolor color	annotation bounding box color
		//		-unique-colors	discard all but one of any pixel color.
		//			-units type	the units of image resolution
		//		-unsharp geometry	sharpen the image
		//		-verbose	print detailed information about the image
		//		-version	print version information
		//		-view	FlashPix viewing transforms
		//		-vignette geometry	soften the edges of the image in vignette style
		//		-virtual-pixel method	access method for pixels outside the boundaries of the image
		//		-wave geometry	alter an image along a sine wave
		//		-weight type	render text with this font weight
		//		-white-point point	chromaticity white point
		//		-white-threshold value	force all pixels above the threshold into white
		//		-write filename	write images to this file
		//--------------------------------------------------------------------------
		//
		// Protected methods
		//
		//--------------------------------------------------------------------------
		
		//--------------------------------------------------------------------------
		//
		// Private methods
		//
		//--------------------------------------------------------------------------
	}
	
}