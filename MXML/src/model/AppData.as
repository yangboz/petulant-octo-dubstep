
package model
{
	import flash.geom.Point;

	//--------------------------------------------------------------------------
	//
	// Imports
	//
	//--------------------------------------------------------------------------
	[Bindable]
	/**
	 * AppData.as class. 
	 * @author yangboz
	 * @langVersion 3.0
	 * @playerVersion 11.2+
	 * @airVersion 3.2+
	 * Created Jun 20, 2014 11:33:09 AM
	 * @history 12/30/13,
	 */ 
	public class AppData
	{ 
		//--------------------------------------------------------------------------
		//
		// Variables
		//
		//--------------------------------------------------------------------------
		public static var mainApp:Main;
		//
		public static var selectedCertSizeIndex:int = -1;
		public static var selectedTypesetSizeIndex:int = -1;
		
		//----------------------------------
		// CONSTANTS
		//----------------------------------
		public static const VIEW_INTRO:int = 0;
		public static const VIEW_UPLOAD:int = 1;
		public static const VIEW_EIDTOR:int = 2;
		public static const VIEW_VERIFING:int = 3;
		public static const VIEW_VERIFIED:int = 4;
		public static const VIEW_TYPESET:int = 5;
		///EmbededAssets
		[Embed(source="assets/images/background/pattern_window_background_01.png")]
		public static var BG_IMG_00:Class;
		[Embed(source="assets/images/background/pattern_window_background_02.png")]
		public static var BG_IMG_01:Class;
		[Embed(source="assets/images/background/pattern_window_background_03.png")]
		public static var BG_IMG_02:Class;
		///CertSizes
		public static const ARRAY_SIZE_CERTS:Array = [
			new Point(140, 196), new Point(132, 192), new Point(156, 227), 
			new Point(154, 220), new Point(154, 198), new Point(200, 200) 
		];
		///TypesetSizes
		public static const ARRAY_SIZE_TYPESET:Array = [
			new Point(220, 320), new Point(480, 330), new Point(480, 330)
		];
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
		public function AppData()
		{
		} 
		//--------------------------------------------------------------------------
		//
		// Public methods
		//
		//--------------------------------------------------------------------------
		
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