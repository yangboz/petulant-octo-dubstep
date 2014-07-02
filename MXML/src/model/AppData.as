
package model
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.events.Event;
	import flash.filesystem.File;
	import flash.filesystem.FileMode;
	import flash.filesystem.FileStream;
	import flash.geom.Matrix;
	import flash.geom.Point;
	import flash.net.dns.AAAARecord;
	import flash.utils.ByteArray;
	
	import mx.core.FlexGlobals;
	import mx.graphics.codec.JPEGEncoder;
	import mx.graphics.codec.PNGEncoder;
	import mx.managers.PopUpManager;
	import mx.utils.UIDUtil;
	
	import views.popups.Popup_ImageVerify_Result;

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
		//
		private static const FILE_NAME_DEFAULT:String = "HP_ID_Print_";
		private static const FILE_ANME_EXT_DEFAULT:String = ".jpg";
		public static var selectedFileName:String;
		public static var selectedFileExt:String;
		//
		public static var uploadedImageFile:File;
		public static var savedImageFie:File;
		public static var savedImageBitmapData:BitmapData;
		public static var savedImageMatrix:Matrix;
		//
		public static var ppi2dpi:Number = 0.3;
		//
		private static var fileStream:FileStream;
		//
		private static var autoCloseWindow:Boolean;
		//----------------------------------
		// CONSTANTS
		//----------------------------------
		//CenterMeter to Inch
		private static const CENTER_METER_2_INCH:Number = 0.3937008;
		//mm*0.3937008*DPI
		//Inch to pixel
		private static const INCH_2_PIXEL:Number = 7.2;
		//
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
		///Upload_photo_frames
		////Instruction text
		public static var ARRAY_INS_CERT_TEXTS:Array = [
			"assets/images/background/text/infomation_editphoto_01.png",
			"assets/images/background/text/infomation_editphoto_02.png",
			"assets/images/background/text/infomation_editphoto_03.png",
			"assets/images/background/text/infomation_editphoto_05.png",
			"assets/images/background/text/infomation_editphoto_04.png",
			"assets/images/background/text/infomation_editphoto_06.png"
		];
		//
		public static var ARRAY_UPLOAD_PHOTO_FRAMES:Array = [
			"assets/images/Photo_25x35/pattern_upload_photo_frame_25x35.png",
			"assets/images/Photo_22x32/pattern_upload_photo_frame_22x32.png",
			"assets/images/Photo_33x48/pattern_upload_photo_frame_33x48.png",
			"assets/images/Photo_35x45/pattern_upload_photo_frame_35x45.png",
			"assets/images/Photo_35x50/pattern_upload_photo_frame_35x50.png",
			"assets/images/Photo_50x50/pattern_upload_photo_frame_50x50.png"
		];
		//
		public static var ARRAY_UPLOAD_PHOTO_GUIDES:Array = [
			"assets/images/Photo_25x35/pattern_upload_photo_guide_25x35.png",
			"assets/images/Photo_22x32/pattern_upload_photo_guide_22x32.png",
			"assets/images/Photo_33x48/pattern_upload_photo_guide_33x48.png",
			"assets/images/Photo_35x45/pattern_upload_photo_guide_35x45.png",
			"assets/images/Photo_35x50/pattern_upload_photo_guide_35x50.png",
			"assets/images/Photo_50x50/pattern_upload_photo_guide_50x50.png"
		];
		//
		//
		public static var ARRAY_UPLOAD_PHOTO_NOTICES:Array = [
			"assets/images/Photo_25x35/pattern_upload_photo_notice_25x35.png",
			"assets/images/Photo_22x32/pattern_upload_photo_notice_22x32.png",
			"assets/images/Photo_33x48/pattern_upload_photo_notice_33x48.png",
			"assets/images/Photo_35x45/pattern_upload_photo_notice_35x45.png",
			"assets/images/Photo_35x50/pattern_upload_photo_notice_35x50.png",
			"assets/images/Photo_50x50/pattern_upload_photo_notice_50x50.png"
		];
		//default file sizes of certificates
		public static var ARRAY_UPLOAD_FILE_SIZES:Array = [
			new Point(14336, 30720), new Point(40960, 51200), new Point(40960, 51200), 
			new Point(40960, 51200), new Point(40960, 51200), new Point(40960, 51200) 
		];
		///EditorView_photos
		//
		public static var ARRAY_EDITOR_PHOTO_FRAMES:Array = [
			"assets/images/Photo_25x35/pattern_edit_photo_frame_25x35.png",
			"assets/images/Photo_22x32/pattern_edit_photo_frame_22x32.png",
			"assets/images/Photo_33x48/pattern_edit_photo_frame_33x48.png",
			"assets/images/Photo_35x45/pattern_edit_photo_frame_35x45.png",
			"assets/images/Photo_35x50/pattern_edit_photo_frame_35x50.png",
			"assets/images/Photo_50x50/pattern_edit_photo_frame_50x50.png"
		];
		public static const ARRAY_EDITOR_POINT_PHOTOS:Array = [
			new Point(423, 187), new Point(427, 187), new Point(415, 187), 
			new Point(416, 187), new Point(416, 187), new Point(393, 187)
		];
		public static const ARRAY_EDITOR_POINT_FRAMES:Array = [
			new Point(421, 185), new Point(425, 185), new Point(413, 185), 
			new Point(414, 185), new Point(414, 185), new Point(391, 185)
		];
		public static const ARRAY_EDITOR_POINT_GUIDES:Array = [
			new Point(421, 185), new Point(425, 185), new Point(413, 185), 
			new Point(414, 185), new Point(414, 185), new Point(391, 185)
		];
		//
		public static var ARRAY_EDITOR_PHOTO_GUIDES:Array = [
			"assets/images/Photo_25x35/pattern_edit_photo_guide_25x35.png",
			"assets/images/Photo_22x32/pattern_edit_photo_guide_22x32.png",
			"assets/images/Photo_33x48/pattern_edit_photo_guide_33x48.png",
			"assets/images/Photo_35x45/pattern_edit_photo_guide_35x45.png",
			"assets/images/Photo_35x50/pattern_edit_photo_guide_35x50.png",
			"assets/images/Photo_50x50/pattern_edit_photo_guide_50x50.png"
		];
		//
		[Embed(source="assets/images/background/text/pattern_detecting.png")]
		public static var INS_VERIFING_TEXT:Class;
		[Embed(source="assets/images/editphoto/pattern_loading_circle_01.png")]
		public static var INS_VERIFING_IMAGE:Class;
		[Embed(source="assets/images/background/text/pattern_detected.png")]
		public static var INS_VERIFIED_TEXT:Class;
		///Verified_view_frame
		public static var ARRAY_VERIFIED_PHOTO_FRAMES:Array = [
			"assets/images/Photo_25x35/pattern_detected_photo_25x35_bg.png",
			"assets/images/Photo_22x32/pattern_detected_photo_22x32.png",
			"assets/images/Photo_33x48/pattern_detected_photo_33x48_bg.png",
			"assets/images/Photo_35x45/pattern_detected_photo_35x45.png",
			"assets/images/Photo_35x50/pattern_detected_photo_35x50.png",
			"assets/images/Photo_50x50/pattern_detected_photo_50x50_bg.png"
		];
		///Verified_result_related
		[Embed(source="assets/images/editphoto/pattern_detacting_text_03.png")]
		public static var INS_VERIFIED_LABLE_00:Class;
		[Embed(source="assets/images/editphoto/pattern_detacting_text_01.png")]
		public static var INS_VERIFIED_LABLE_01:Class;
		[Embed(source="assets/images/editphoto/pattern_detacting_text_02.png")]
		public static var INS_VERIFIED_LABLE_02:Class;
		[Embed(source="assets/images/editphoto/icon_checklist_error.png")]
		public static var INS_VERIFIED_RESULT_ERROR:Class;
		[Embed(source="assets/images/editphoto/icon_checklist_pass.png")]
		public static var INS_VERIFIED_RESULT_PASS:Class;
		///
		public static const ARRAY_VERIFIED_POINT_PHOTO:Array = [
			new Point(346, 187), new Point(350, 187), new Point(338, 187), 
			new Point(339, 187), new Point(339, 187), new Point(316, 187)
		];
		public static const ARRAY_VERIFIED_POINT_FRAMES:Array = [
			new Point(342, 183), new Point(346, 183), new Point(334, 183), 
			new Point(335, 183), new Point(335, 183), new Point(312, 183)
		];
		///CertSizes(标准一寸,小一寸,大一寸,标准二寸,小二寸,赴美签证)
		public static const ARRAY_SIZE_CERTS:Array = [
			new Point(140, 196), new Point(132, 192), new Point(156, 227), 
			new Point(154, 198), new Point(154, 220), new Point(200, 200) 
		];
		///TypesetSizes
		public static const ARRAY_SIZE_TYPESET:Array = [
			new Point(220, 320), new Point(480, 330), new Point(480, 330)
		];
		public static var ARRAY_TYPESET_FRAMES:Array = [
			"assets/images/photo_on_paper/pattern_photo_on_paper_4x6.png",
			"assets/images/photo_on_paper/pattern_photo_on_paper_5x7.png",
			"assets/images/photo_on_paper/pattern_photo_on_paper_a4.png"
		];
		private static var ARRAY_TYPESET_TILE_IMAGE_4x6:Array = [
			"assets/images/photo_on_paper/4x6/pattern_photo_on_paper_25x35on4x6.png",
			"assets/images/photo_on_paper/4x6/pattern_photo_on_paper_22x32on4x6.png",
			"assets/images/photo_on_paper/4x6/pattern_photo_on_paper_33x48on4x6.png",
			"assets/images/photo_on_paper/4x6/pattern_photo_on_paper_35x50on4x6.png",
			"assets/images/photo_on_paper/4x6/pattern_photo_on_paper_35x45on4x6.png",
			"assets/images/photo_on_paper/4x6/pattern_photo_on_paper_50X50on4x6.png"
		];
		private static var ARRAY_TYPESET_TILE_SIZE_4x6:Array = [
			new Point(2,5),new Point(2,5),new Point(2,4),
			new Point(2,4),new Point(2,4),new Point(1,2)
		];
		//mm*0.3937008*DPI
		//2.8368
		private static var ARRAY_TYPESET_TILE_POINT_4x6:Array = [
			{x:101,y:128,w:25*2.8368,h:35*2.8368,r:0},{x:126,y:135,w:22*2.8368,h:32*2.8362,r:0},{x:96,y:92,w:33*2.8368,h:48*2.8368,r:0},
			{x:77,y:105,w:30*2.8368,h:45*2.8368,r:0},{x:82,y:91,w:35*2.8368,h:50*2.8368,r:0},{x:143,y:158,w:50*2.8368,h:50*2.8368,r:0},
		];
		private static var ARRAY_TYPESET_TILE_IMAGE_5x7:Array = [
			"assets/images/photo_on_paper/5x7/pattern_photo_on_paper_25x35on5x7.png",
			"assets/images/photo_on_paper/5x7/pattern_photo_on_paper_22x32on5x7.png",
			"assets/images/photo_on_paper/5x7/pattern_photo_on_paper_33x48on5x7.png",
			"assets/images/photo_on_paper/5x7/pattern_photo_on_paper_35x50on5x7.png",
			"assets/images/photo_on_paper/5x7/pattern_photo_on_paper_35x45on5x7.png",
			"assets/images/photo_on_paper/5x7/pattern_photo_on_paper_50X50on5x7.png"
		];
		private static var ARRAY_TYPESET_TILE_SIZE_5x7:Array = [
			new Point(3,4),new Point(3,4),new Point(2,4),
			new Point(2,4),new Point(2,4),new Point(2,3)
		];
		private static var ARRAY_TYPESET_TILE_POINT_5x7:Array = [
			{x:100,y:96,w:25*2.8368,h:35*2.8368,r:0},{x:100,y:107,w:22*2.8368,h:32*2.8362,r:0},{x:120,y:105,w:33*2.8368,h:48*2.8368,r:0},
			{x:106,y:103,w:30*2.8368,h:45*2.8368,r:0},{x:110,y:111,w:35*2.8368,h:50*2.8368,r:0},{x:97,y:103,w:50*2.8368,h:50*2.8368,r:0},
		];
		private static var ARRAY_TYPESET_TILE_IMAGE_A4:Array = [
			"assets/images/photo_on_paper/A4/pattern_photo_on_paper_25x35ona4.png",
			"assets/images/photo_on_paper/A4/pattern_photo_on_paper_22x32ona4.png",
			"assets/images/photo_on_paper/A4/pattern_photo_on_paper_33x48ona4.png",
			"assets/images/photo_on_paper/A4/pattern_photo_on_paper_35x50ona4.png",
			"assets/images/photo_on_paper/A4/pattern_photo_on_paper_35x45ona4.png",
			"assets/images/photo_on_paper/A4/pattern_photo_on_paper_50X50ona4.png"
		];
		private static var ARRAY_TYPESET_TILE_SIZE_A4:Array = [
			new Point(7,2),new Point(8,2),new Point(5,2),
			new Point(5,2),new Point(5,2),new Point(3,2)
		];
		private static var ARRAY_TYPESET_TILE_POINT_A4:Array = [
			{x:70,y:83,w:25*2.8368,h:35*2.8368,r:270},{x:71,y:83,w:22*2.8368,h:32*2.8362,r:270},{x:69,y:94,w:33*2.8368,h:48*2.8368,r:270},
			{x:70,y:83,w:30*2.8368,h:45*2.8368,r:270},{x:67,y:86,w:35*2.8368,h:50*2.8368,r:270},{x:70,y:108,w:50*2.8368,h:50*2.8368,r:270},
		];
		//
		public static var ARRAY_TYPESET_TILE_IMGS:Array = [
			ARRAY_TYPESET_TILE_IMAGE_4x6,
			ARRAY_TYPESET_TILE_IMAGE_5x7,
			ARRAY_TYPESET_TILE_IMAGE_A4
		];
		public static var ARRAY_TYPESET_TILE_SIZE:Array = [
			ARRAY_TYPESET_TILE_SIZE_4x6,
			ARRAY_TYPESET_TILE_SIZE_5x7,
			ARRAY_TYPESET_TILE_SIZE_A4
		];
		public static var ARRAY_TYPESET_TILE_POINT:Array = [
			ARRAY_TYPESET_TILE_POINT_4x6,
			ARRAY_TYPESET_TILE_POINT_5x7,
			ARRAY_TYPESET_TILE_POINT_A4
		];
		///ImageVerify notifications
		[Embed(source="assets/images/notification/pattern_notification_01.png")]
		public static var NOTIFY_IMG_VERIFY_RESULT_0:Class;
		[Embed(source="assets/images/notification/pattern_notification_03.png")]
		public static var NOTIFY_IMG_VERIFY_RESULT_1:Class;
		[Embed(source="assets/images/notification/pattern_notification_02.png")]
		public static var NOTIFY_IMG_SAVE_RESULT:Class;
		///Close Window
		[Embed(source="assets/images/close_window/pattern_window_close_bg.png")]
		public static var ALERT_CLOSE_WINDOW_BG:Class;
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
		public static function popup_image_verify_result(bgClass:Class):void
		{
			var popup:Popup_ImageVerify_Result = new Popup_ImageVerify_Result();
//			popup.setStyle("backgroundImage",new bgClass() as Bitmap);
//			popup.image_source = new bgClass() as Bitmap;
			//				menuPopup.open(this, true);
			popup.open(FlexGlobals.topLevelApplication as DisplayObjectContainer, true);
			PopUpManager.centerPopUp(popup);
		}
		//
		public static function saveImageFile(bitmapData:BitmapData,dialog:Boolean=false,extension:String=".jpg",autoCloseWindow:Boolean=false):Boolean
		{
			//
			AppData.autoCloseWindow = autoCloseWindow;
			//
			var saved:Boolean = false;
			//
			var pngEncoder:PNGEncoder = new PNGEncoder(); 
			var jpgEncoder:JPEGEncoder = new JPEGEncoder(100);
			var imageByteArray:ByteArray;
			//
			if(extension==".jpg")
			{
				imageByteArray = jpgEncoder.encode(bitmapData); 
			}else//*.png
			{
				imageByteArray = pngEncoder.encode(bitmapData); 
			}
			//
			AppData.savedImageBitmapData = bitmapData;
			//
			AppData.selectedFileExt = extension;
//			AppData.selectedFileName = AppData.FILE_NAME_DEFAULT.concat(extension);
			AppData.selectedFileName = getClassifiedFileName().concat(extension);
			//Kind of file save options here:
			AppData.savedImageFie = File.documentsDirectory;
//			AppData.savedImageFie = File.applicationDirectory;
//			AppData.savedImageFie = File.applicationStorageDirectory;
			//
			if(dialog)
			{
				AppData.savedImageFie.save(imageByteArray,AppData.selectedFileName);
//				trace("AppData.savedImageFie(with dialog):",AppData.savedImageFie.nativePath);
				AppData.savedImageFie.addEventListener(Event.COMPLETE,complateHandler);
				function complateHandler(event:Event):void
				{
					if(AppData.autoCloseWindow)
					{
						AppData.mainApp.nativeWindow.close();
					}
				}
			}else
			{
				AppData.savedImageFie=AppData.savedImageFie.resolvePath(AppData.selectedFileName);  
				//
				fileStream = new FileStream();  
				fileStream.open(AppData.savedImageFie, FileMode.WRITE);  
				fileStream.writeBytes(imageByteArray);
//				fileStream.writeUTFBytes("Hi this file was saved from AIR application without dialog");  
				fileStream.addEventListener(Event.CLOSE, fileStreamCloseHandler);  
				fileStream.close();  
				trace("AppData.savedImageFie(without dialog):",AppData.savedImageFie.nativePath);
			}
//			
			//
			return saved;
		}
		//mm*0.3937008*DPI
		public static function centerMeterToPixel(value:Number):Number
		{
			return value*CENTER_METER_2_INCH*INCH_2_PIXEL;
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
		private static function fileStreamCloseHandler(event:Event):void 
		{  
			trace("fileStreamCloseHandler fired!");  
			fileStream.removeEventListener(Event.CLOSE, fileStreamCloseHandler);
		}  	
		//
		private static function getClassifiedFileName():String
		{
			var fileName:String = FILE_NAME_DEFAULT;
			fileName = fileName.concat(getCertPlainText(selectedCertSizeIndex),"_",getPrintPlainText(selectedTypesetSizeIndex),"_");
			return fileName;
//			return UIDUtil.createUID();
		}
		//
		private static function getCertPlainText(index:int):String
		{
			var certText:String = "???????";
			switch(index)
			{
				case 0:
					certText = "25x35mm";
					break;
				case 1:
					certText = "22x32mm";
					break;
				case 2:
					certText = "33x48mm";
					break;
				case 3:
					certText = "35x45mm";
					break;
				case 4:
					certText = "35x50mm";
					break;
				case 5:
					certText = "50x50mm";
					break;
				default:
					break;
			}
			return certText;
		}
		//
		private static function getPrintPlainText(index:int):String
		{
			var printText:String = "???";
			switch(index)
			{
				case 0:
					printText = "4x6";
					break;
				case 1:
					printText = "5x7";
					break;
				case 2:
					printText = "A4";
					break;
				default:
					break;
			}
			return printText;
		}
	}
	
}