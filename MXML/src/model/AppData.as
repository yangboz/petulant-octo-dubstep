
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
		////Instruction text
		[Embed(source="assets/images/background/text/infomation_editphoto_01.png")]
		private static var INS_CERT_TEXT_00:Class;
		[Embed(source="assets/images/background/text/infomation_editphoto_02.png")]
		private static var INS_CERT_TEXT_01:Class;
		[Embed(source="assets/images/background/text/infomation_editphoto_03.png")]
		private static var INS_CERT_TEXT_02:Class;
		[Embed(source="assets/images/background/text/infomation_editphoto_04.png")]
		private static var INS_CERT_TEXT_03:Class;
		[Embed(source="assets/images/background/text/infomation_editphoto_05.png")]
		private static var INS_CERT_TEXT_04:Class;
		[Embed(source="assets/images/background/text/infomation_editphoto_06.png")]
		private static var INS_CERT_TEXT_05:Class;
		//
		public static var ARRAY_INS_CERT_TEXTS:Array = [
			new INS_CERT_TEXT_00(),new INS_CERT_TEXT_01(),new INS_CERT_TEXT_02(),
			new INS_CERT_TEXT_03(),new INS_CERT_TEXT_04(),new INS_CERT_TEXT_05()
		];
		//
		[Embed(source="assets/images/background/text/pattern_detecting.png")]
		public static var INS_VERIFING_TEXT:Class;
		[Embed(source="assets/images/background/text/pattern_detected.png")]
		public static var INS_VERIFIED_TEXT:Class;
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