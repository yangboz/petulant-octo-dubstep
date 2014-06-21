
package model
{
	import flash.filesystem.File;
	import flash.geom.Point;
	import flash.net.dns.AAAARecord;

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
		public static var selectedTypesetSizeIndex:int = 0;
		public static var uploadedImageFile:File;
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
		///Upload_photo_frames
//		[Embed(source="assets/images/Photo_22x32/pattern_upload_photo_frame_22x32.png")]
//		private static var UPLOAD_PHOTO_FRAME_00:Class;
//		[Embed(source="assets/images/Photo_25x35/pattern_upload_photo_frame_25x35.png")]
//		private static var UPLOAD_PHOTO_FRAME_01:Class;
//		[Embed(source="assets/images/Photo_33x48/pattern_upload_photo_frame_33x48.png")]
//		private static var UPLOAD_PHOTO_FRAME_02:Class;
//		[Embed(source="assets/images/Photo_35x45/pattern_upload_photo_frame_35x45.png")]
//		private static var UPLOAD_PHOTO_FRAME_03:Class;
//		[Embed(source="assets/images/Photo_35x50/pattern_upload_photo_frame_35x50.png")]
//		private static var UPLOAD_PHOTO_FRAME_04:Class;
//		[Embed(source="assets/images/Photo_50x50/pattern_upload_photo_frame_50x50.png")]
//		private static var UPLOAD_PHOTO_FRAME_05:Class;
		///Upload_photo_guides
//		[Embed(source="assets/images/Photo_22x32/pattern_upload_photo_guide_22x32.png")]
//		private static var UPLOAD_PHOTO_GUIDE_00:Class;
//		[Embed(source="assets/images/Photo_25x35/pattern_upload_photo_guide_25x35.png")]
//		private static var UPLOAD_PHOTO_GUIDE_01:Class;
//		[Embed(source="assets/images/Photo_33x48/pattern_upload_photo_guide_33x48.png")]
//		private static var UPLOAD_PHOTO_GUIDE_02:Class;
//		[Embed(source="assets/images/Photo_35x45/pattern_upload_photo_guide_35x45.png")]
//		private static var UPLOAD_PHOTO_GUIDE_03:Class;
//		[Embed(source="assets/images/Photo_35x50/pattern_upload_photo_guide_35x50.png")]
//		private static var UPLOAD_PHOTO_GUIDE_04:Class;
//		[Embed(source="assets/images/Photo_50x50/pattern_upload_photo_guide_50x50.png")]
//		private static var UPLOAD_PHOTO_GUIDE_05:Class;
		///Upload_photo_notices
//		[Embed(source="assets/images/Photo_22x32/pattern_upload_photo_notice_22x32.png")]
//		private static var UPLOAD_PHOTO_NOTICE_00:Class;
//		[Embed(source="assets/images/Photo_25x35/pattern_upload_photo_notice_25x35.png")]
//		private static var UPLOAD_PHOTO_NOTICE_01:Class;
//		[Embed(source="assets/images/Photo_33x48/pattern_upload_photo_notice_33x48.png")]
//		private static var UPLOAD_PHOTO_NOTICE_02:Class;
//		[Embed(source="assets/images/Photo_35x45/pattern_upload_photo_notice_35x45.png")]
//		private static var UPLOAD_PHOTO_NOTICE_03:Class;
//		[Embed(source="assets/images/Photo_35x50/pattern_upload_photo_notice_35x50.png")]
//		private static var UPLOAD_PHOTO_NOTICE_04:Class;
//		[Embed(source="assets/images/Photo_50x50/pattern_upload_photo_notice_50x50.png")]
//		private static var UPLOAD_PHOTO_NOTICE_05:Class;
		//
		public static var ARRAY_INS_CERT_TEXTS:Array = [
			new INS_CERT_TEXT_00(),new INS_CERT_TEXT_01(),new INS_CERT_TEXT_02(),
			new INS_CERT_TEXT_03(),new INS_CERT_TEXT_04(),new INS_CERT_TEXT_05()
		];
		//
//		public static var ARRAY_UPLOAD_PHOTO_FRAMES:Array = [
//			new UPLOAD_PHOTO_FRAME_00(),new UPLOAD_PHOTO_FRAME_01(),new UPLOAD_PHOTO_FRAME_02(),
//			new UPLOAD_PHOTO_FRAME_03(),new UPLOAD_PHOTO_FRAME_04(),new UPLOAD_PHOTO_FRAME_05()
//		];
		//
		public static var ARRAY_UPLOAD_PHOTO_FRAMES:Array = [
			"assets/images/Photo_22x32/pattern_upload_photo_frame_22x32.png","assets/images/Photo_25x35/pattern_upload_photo_frame_25x35.png","assets/images/Photo_33x48/pattern_upload_photo_frame_33x48.png",
			"assets/images/Photo_35x45/pattern_upload_photo_frame_35x45.png","assets/images/Photo_35x50/pattern_upload_photo_frame_35x50.png","assets/images/Photo_50x50/pattern_upload_photo_frame_50x50.png"
		];
		//
//		public static var ARRAY_UPLOAD_PHOTO_GUIDES:Array = [
//			new UPLOAD_PHOTO_GUIDE_00(),new UPLOAD_PHOTO_GUIDE_01(),new UPLOAD_PHOTO_GUIDE_02(),
//			new UPLOAD_PHOTO_GUIDE_03(),new UPLOAD_PHOTO_GUIDE_04(),new UPLOAD_PHOTO_GUIDE_05()
//		];
		//
		public static var ARRAY_UPLOAD_PHOTO_GUIDES:Array = [
			"assets/images/Photo_22x32/pattern_upload_photo_guide_22x32.png","assets/images/Photo_25x35/pattern_upload_photo_guide_25x35.png","assets/images/Photo_33x48/pattern_upload_photo_guide_33x48.png",
			"assets/images/Photo_35x45/pattern_upload_photo_guide_35x45.png","assets/images/Photo_35x50/pattern_upload_photo_guide_35x50.png","assets/images/Photo_50x50/pattern_upload_photo_guide_50x50.png"
		];
		//
//		public static var ARRAY_UPLOAD_PHOTO_NOTICES:Array = [
//			new UPLOAD_PHOTO_NOTICE_00(),new UPLOAD_PHOTO_NOTICE_01(),new UPLOAD_PHOTO_NOTICE_02(),
//			new UPLOAD_PHOTO_NOTICE_03(),new UPLOAD_PHOTO_NOTICE_04(),new UPLOAD_PHOTO_NOTICE_05()
//		];
		//
		public static var ARRAY_UPLOAD_PHOTO_NOTICES:Array = [
			"assets/images/Photo_22x32/pattern_upload_photo_notice_22x32.png","assets/images/Photo_25x35/pattern_upload_photo_notice_25x35.png","assets/images/Photo_33x48/pattern_upload_photo_notice_33x48.png",
			"assets/images/Photo_35x45/pattern_upload_photo_notice_35x45.png","assets/images/Photo_35x50/pattern_upload_photo_notice_35x50.png","assets/images/Photo_50x50/pattern_upload_photo_notice_50x50.png"
		];
		///EditorView_photos
		//
		public static var ARRAY_EDITOR_PHOTO_FRAMES:Array = [
			"assets/images/Photo_22x32/pattern_edit_photo_frame_22x32.png","assets/images/Photo_25x35/pattern_edit_photo_frame_25x35.png","assets/images/Photo_33x48/pattern_edit_photo_frame_33x48.png",
			"assets/images/Photo_35x45/pattern_edit_photo_frame_35x45.png","assets/images/Photo_35x50/pattern_edit_photo_frame_35x50.png","assets/images/Photo_50x50/pattern_edit_photo_frame_50x50.png"
		];
		//
		public static var ARRAY_EDITOR_PHOTO_GUIDES:Array = [
			"assets/images/Photo_22x32/pattern_edit_photo_guide_22x32.png","assets/images/Photo_25x35/pattern_edit_photo_guide_25x35.png","assets/images/Photo_33x48/pattern_edit_photo_guide_33x48.png",
			"assets/images/Photo_35x45/pattern_edit_photo_guide_35x45.png","assets/images/Photo_35x50/pattern_edit_photo_guide_35x50.png","assets/images/Photo_50x50/pattern_edit_photo_guide_50x50.png"
		];
		//
		[Embed(source="assets/images/background/text/pattern_detecting.png")]
		public static var INS_VERIFING_TEXT:Class;
		[Embed(source="assets/images/background/text/pattern_detected.png")]
		public static var INS_VERIFIED_TEXT:Class;
		///Verified_view_frame
		public static var ARRAY_VERIFIED_PHOTO_FRAMES:Array = [
			"assets/images/Photo_22x32/pattern_detected_photo_22x32.png","assets/images/Photo_25x35/pattern_detected_photo_25x35_bg.png","assets/images/Photo_33x48/pattern_detected_photo_33x48_bg.png",
			"assets/images/Photo_35x45/pattern_detected_photo_35x45.png","assets/images/Photo_35x50/pattern_detected_photo_35x50.png","assets/images/Photo_50x50/pattern_detected_photo_50x50_bg.png"
		];
		///CertSizes
		public static const ARRAY_SIZE_CERTS:Array = [
			new Point(140, 196), new Point(132, 192), new Point(156, 227), 
			new Point(154, 220), new Point(154, 198), new Point(200, 200) 
		];
		///TypesetSizes
		public static const ARRAY_SIZE_TYPESET:Array = [
			new Point(220, 320), new Point(480, 330), new Point(480, 330)
		];
		public static var ARRAY_TYPESET_FRAMES:Array = [
			"assets/images/photo_on_paper/pattern_photo_on_paper_4x6.png","assets/images/photo_on_paper/pattern_photo_on_paper_5x7.png","assets/images/photo_on_paper/pattern_photo_on_paper_a4.png"
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