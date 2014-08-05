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
//	import com.godpaper.as3.utils.LogUtil;
//	
//	import mx.logging.ILogger;

	//--------------------------------------------------------------------------
	//
	// Imports
	//
	//--------------------------------------------------------------------------
	[ExcludeClass]//Avoid directly call.
	/**
	 * ImageMagickParameters.as class. 
	 * @author yangboz
	 * @langVersion 3.0
	 * @playerVersion 11.2+
	 * @airVersion 3.2+
	 * Created Jan 17, 2014 1:13:17 PM
	 * @history 12/30/13,
	 */ 
	public class ImageMagickParameters
	{ 
		//--------------------------------------------------------------------------
		//
		// Variables
		//
		//--------------------------------------------------------------------------
		//@required
		/**
		 * @see http://help.adobe.com/en_US/ActionScript/3.0_ProgrammingAS3/WS5b3ccc516d4fbf351e63e3d118a9b90204-7f56.html
		 * @see http://www.imagemagick.org/Usage/montage/
		 */		
		public static var commandOpt:String = "";//resize/montage command option Strings
		/**
		 * File destination String
		 */	
		public static var desFile:String = 'C:/Users/yangboz/git/cloaked-batman/src/Desert_output.png';
		/**
		 * File source String
		 */		
		public static var srcFile:String = 'C:/Users/yangboz/git/cloaked-batman/src/Desert.jpg';
		//@optional
		//@see http://www.imagemagick.org/script/convert.php#options
		
		//----------------------------------
		// CONSTANTS
		//----------------------------------
//		private static const LOG:ILogger = LogUtil.getLogger(ImageMagickParameters);
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
		public function ImageMagickParameters()
		{
		} 
		//--------------------------------------------------------------------------
		//
		// Public methods
		//
		//--------------------------------------------------------------------------
		static public function toArguments(exeType:String):Vector.<String>
		{
			var exeOptions:String = ":srcFilename,:commandOption,:destFilename"; // command (1)
			//Command string processing
			//Simple String replace
			exeOptions = exeOptions.replace(':srcFilename', ImageMagickParameters.srcFile);
			// command processing
			exeOptions = exeOptions.replace(':commandOption', ImageMagickParameters.commandOpt);
			exeOptions = exeOptions.replace(':destFilename', ImageMagickParameters.desFile);
			var processArgs:Vector.<String> = new Vector.<String>();
			var parts:Array = exeOptions.split(',');
			for (var i:int =0; i<parts.length; i++) {
				processArgs.push(parts[i]);
			}
//			return new Vector.<String>();
//			trace("Native Process Arguments:{0}",processArgs.toString());
			trace("Native Process Arguments:",processArgs.toString());
			return processArgs;
		}
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