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
	
	import flash.desktop.NativeProcess;
	import flash.desktop.NativeProcessStartupInfo;
	import flash.events.Event;
	import flash.events.EventDispatcher;
	import flash.events.ProgressEvent;
	import flash.filesystem.File;
	import flash.utils.IDataInput;
	
	//event metdata declare
	/** Dispatched when a standard ImageMagick input is clos-ed. */
	[Event(name="ImageMagick_standard_input_close", type="com.godpaper.as3.ImageMagick.ImageMagickEvent")]
	
	/** Dispatched when a standard ImageMagick process is input-ed. */
	[Event(name="ImageMagick_input_progress", type="com.godpaper.as3.ImageMagick.ImageMagickEvent")]
	
	/** Dispatched when a standard ImageMagick process is output-ed. */
	[Event(name="ImageMagick_output_data", type="com.godpaper.as3.ImageMagick.ImageMagickEvent")]
	
	/** Dispatched when a standard ImageMagick output is close-ed. */
	[Event(name="ImageMagick_standard_output_close", type="com.godpaper.as3.ImageMagick.ImageMagickEvent")]
	
	/** Dispatched when a standard ImageMagick process is error-ed. */
	[Event(name="ImageMagick_error_data", type="com.godpaper.as3.ImageMagick.ImageMagickEvent")]
	
	/** Dispatched when a standard ImageMagick output is close-ed. */
	[Event(name="ImageMagick_standard_output_error", type="com.godpaper.as3.ImageMagick.ImageMagickEvent")]
	/**
	 * AS3ImageMagick.as class. An AS3 wrapper with ImageMagick features.
	 * @author yangboz
	 * @langVersion 3.0
	 * @playerVersion 11.2+
	 * @airVersion 3.2+
	 * Created Jan 17, 2014 1:34:23 PM
	 * @history 12/30/13,
	 * @see http://help.adobe.com/en_US/air/reference/html/flash/desktop/NativeProcess.html
	 * @see http://www.imagemagick.org/script/architecture.php
	 * @see http://help.adobe.com/en_US/air/html/dev/WSb2ba3b1aad8a27b060d22f991220f00ad8a-8000.html
	 */ 
	public class AS3ImageMagick extends EventDispatcher
	{ 
		//--------------------------------------------------------------------------
		//
		// Variables
		//
		//--------------------------------------------------------------------------
		private var _exe:String = "convert.exe";//others:montage,identify,display,compose...
		private var _nativeProcessStartupInfo:NativeProcessStartupInfo;
		private var _file:File;
		private var _nativeProcess:NativeProcess;
		//
		//----------------------------------
		// CONSTANTS
		//----------------------------------
		//as3Logger
		//		LoggerConfig.filters = ["AS3ImageMagick"];
//		LoggerConfig.filters = ["com.godpaper.as3.ImageMagick.*"];
//		LoggerConfig.level = LogEventLevel.DEBUG;
//		private static const LOG:ILogger = LogUtil.getLogger(AS3ImageMagick);
		//--------------------------------------------------------------------------
		//
		// Public properties
		//
		//--------------------------------------------------------------------------
		/**
		 * AS3ImageMagick warpper used native process,for your custom event listener.
		 * @return 
		 */		
		public function get nativeProcess():NativeProcess
		{
			return _nativeProcess;
		}
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
		 * 
		 * @param exe ImageMagick related *.exe file path.
		 * @param facts ImageMagick builded factors,such as file path,resize option.
		 * 
		 */		
		public function AS3ImageMagick(exe:String,facts:ImageMagickFacts)
		{
			//Initialization here.
			this._exe = exe;
			this._nativeProcessStartupInfo = new NativeProcessStartupInfo(); 
			this._file = File.applicationDirectory.resolvePath(this._exe); 
			this._nativeProcessStartupInfo.executable = this._file;
			this._nativeProcessStartupInfo.workingDirectory = File.applicationDirectory;
			//arguments assemble here.
			this._nativeProcessStartupInfo.arguments = facts.toArguments(exe); 
			//
			this._nativeProcess = new NativeProcess();
			//output handler
			this._nativeProcess.addEventListener(ProgressEvent.STANDARD_OUTPUT_DATA, standardOutputDataHandler); 
			this._nativeProcess.addEventListener(Event.STANDARD_OUTPUT_CLOSE,standardOutputCloseHandler);
			//error handler
			this._nativeProcess.addEventListener(Event.STANDARD_INPUT_CLOSE,standardInputHandler);
			this._nativeProcess.addEventListener(ProgressEvent.STANDARD_INPUT_PROGRESS,standardInputProgressHandler);
			//input handler
			this._nativeProcess.addEventListener(ProgressEvent.STANDARD_ERROR_DATA, standardErrorDataHandler); 
			this._nativeProcess.addEventListener(Event.STANDARD_ERROR_CLOSE,standardErrorCloseHandler);
			//
			super();
		} 
		//--------------------------------------------------------------------------
		//
		// Public methods
		//
		//--------------------------------------------------------------------------
		//
		public function start():void
		{
			this._nativeProcess.start(this._nativeProcessStartupInfo); 
		}
		//
		public function exit(force:Boolean):void
		{
			if(this._nativeProcess.running)
			{
				this._nativeProcess.exit(force);
			}
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
		//output handlers
		//
		private function standardOutputDataHandler(event:ProgressEvent):void
		{ 
//			trace("standardOutputDataHandler(event):{0}",event.toString());
//			trace("standardOutputDataHandler(event):",event.toString());
			var bytes : IDataInput = this._nativeProcess.standardOutput as IDataInput;
            var outputString: String = bytes.readUTFBytes(bytes.bytesAvailable).toString();
//            trace("standardOutputDataHandler(output):{0}",outputString);
// 			trace("standardOutputDataHandler(output):",outputString);
			//dispatch event
			this.dispatchEvent(new ImageMagickEvent(ImageMagickEvent.STANDARD_OUTPUT_DATA));
		}
		//
		private function standardOutputCloseHandler(event:Event):void
		{
//			trace("standardOutputCloseHandler:{0}",event.toString());
//			trace("standardOutputCloseHandler:",event.toString());
			//dispatch event
			this.dispatchEvent(new ImageMagickEvent(ImageMagickEvent.STANDARD_OUTPUT_CLOSE));
			//exit process
			this.exit(false);
		}
		//error handlers
		//
		private function standardErrorDataHandler(event:ProgressEvent):void
		{ 
//			trace("standardErrorDataHandler(event):{0}",event.toString());
//			trace("standardErrorDataHandler(event):{0}",event.toString());
			var bytes : IDataInput = this._nativeProcess.standardError as IDataInput;
            var outputString: String = bytes.readUTFBytes(bytes.bytesAvailable).toString();
//            trace("standardErrorDataHandler:{0}",outputString);
//			trace("standardErrorDataHandler:{0}",outputString);
			//dispatch event
			this.dispatchEvent(new ImageMagickEvent(ImageMagickEvent.STANDARD_ERROR_DATA));
		}
		
		//
		private function standardErrorCloseHandler(event:Event):void
		{
//			trace("standardErrorCloseHandler:{0}",event.toString());
//			trace("standardErrorCloseHandler:{0}",event.toString());
			//dispatch event
			this.dispatchEvent(new ImageMagickEvent(ImageMagickEvent.STANDARD_OUTPUT_ERROR));
			//exit process
			this.exit(false);
		}
		//input handlers
		//
		private function standardInputHandler(event:Event):void
		{
//			trace("standardInputHandler:{0}",event.toString());
			trace("standardInputHandler:{0}",event.toString());
			//dispatch event
			this.dispatchEvent(new ImageMagickEvent(ImageMagickEvent.STANDARD_INPUT_PROGRESS));
		}
		//
		private function standardInputProgressHandler(event:Event):void
		{
//			trace("standardInputProgressHandler:{0}",event.toString());
			trace("standardInputProgressHandler:{0}",event.toString());
			//dispatch event
			this.dispatchEvent(new ImageMagickEvent(ImageMagickEvent.STANDARD_INPUT_PROGRESS));
		}
	}
	
}