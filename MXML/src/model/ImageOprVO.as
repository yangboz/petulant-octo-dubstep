package model
{
	import flash.geom.Rectangle;
	
	import mx.utils.ObjectUtil;

	/**
	 * Image Operation Value Objects related to ImageMagick command and parameters.
	 * @author yangboz
	 * @see http://www.imagemagick.org/Usage/
	 * @example: convert C:\\image.JPG -resize 333x500 -page 333x333+0+0 -rotate 30 -crop 333x333+0+0 -background white -flatten C:\\output_resize_page_rotate_crop.png
	 */	
	public class ImageOprVO extends Object
	{
		//RequiredWidth/Height
		public var requiredWidth:Number;
		public var requiredHeight:Number;
		//UITransformTool related.
		public var tX:Number=0;//TranslateX related on UITransformTool
		public var tY:Number=0;//TranslateY related on UITransformTool
		public var iScaleX:Number=1;//ScaleX related on UITransformTool at Initialization
		public var iScaleY:Number=1;//ScaleY related on UITransformTool at Initialization
		public var uScaleX:Number=1;//ScaleX value by user(slider,resize cropper);
		public var uScaleY:Number=1;//ScaleY value by user(slider,resize cropper);
		//Rotation,UITransformTool or VSlider_rotate.
		public var r:Number=0;
		//Crop value for ImageMagick -crop,@see http://www.imagemagick.org/Usage/crop/#crop_viewport
		public function get cropHeight():Number
		{
			return requiredHeight*uScaleY;
		}
		
		public function get cropWidth():Number
		{
			return requiredWidth*uScaleX;
		}
		//Page(viewPoint) value for ImageMagick -page,@see http://www.imagemagick.org/Usage/layers/#flatten
		public function get pageHeight():Number
		{
			return requiredHeight*uScaleY;
		}
		
		public function get pageWidth():Number
		{
			return requiredWidth*uScaleX;
		}
		//ImageMagick -page offset values
		public var offsetPx:String="+0";//OffsetX
		public var offsetPy:String="+0";//OffsetY
		//ImageMagick -crop offset values
		//OffsetX
		public function get offsetCx():String
		{
			return tX>=0?String("+").concat(tX):tX.toString();
		}
		//OffsetY
		public function get offsetCy():String
		{
			return tY>=0?String("+").concat(tY):tY.toString();
		}
		//ImageMagick -resize(zoomIn/Out) values
		public var resizeWidth:Number=0;
		public var resizeHeight:Number=0;
		//For debugging
		public function toString():String
		{
			return ObjectUtil.toString(this);
		}
		
	}
}