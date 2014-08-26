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
		//UITransformTool related.
		public var tX:Number=0;//TranslateX related on UITransformTool
		public var tY:Number=0;//TranslateY related on UITransformTool
		public var scaleX:Number=1;//ScaleX related on UITransformTool
		public var scaleY:Number=1;//ScaleY related on UITransformTool
		//Rotation
		public var r:Number=0;
		//Crop value for ImageMagick -crop,@see http://www.imagemagick.org/Usage/crop/#crop_viewport
		public var cropWidth:Number = 0;
		public var cropHeight:Number = 0;
		//Page(viewPoint) value for ImageMagick -page,@see http://www.imagemagick.org/Usage/layers/#flatten
		public var pageWidth:Number=0;//Page view width
		public var pageHeight:Number=0;//Page view height
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