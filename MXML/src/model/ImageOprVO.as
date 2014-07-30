package model
{
	import mx.utils.ObjectUtil;

	public class ImageOprVO extends Object
	{
		public var sX:Number=1;//ScaleX
		public var sY:Number=1;//ScaleY
		public var tX:Number=0;//TranslateX
		public var tY:Number=0;//TranslateY
		public var r:Number=0;//Rotation
		//Offset value for ImageMagick -crop
		public var oX:Number=0;//OffsetX
		public var oY:Number=0;//OffsetY
		//Original image size
//		public var oW:Number=0;
//		public var oH:Number=0;
		//
		public function toString():String
		{
			return ObjectUtil.toString(this);
		}
	}
}