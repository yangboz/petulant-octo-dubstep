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
		public var osX:Number=1;//Default/orignal ScaleX
		public var osY:Number=1;//Default/orignal ScaleY
//		public var usX:Number=1;//User ScaleX
//		public var usY:Number=1;//User ScaleY
		//
		public var tX:Number=0;//TranslateX
		public var tY:Number=0;//TranslateY
		//
		public var r:Number=0;//Rotation
		//Offset value for ImageMagick -crop
		private var _oX:Number=0;//OffsetX
		private var _oY:Number=0;//OffsetY
		//Original image size
		public var oW:Number=0;
		public var oH:Number=0;
		//Required area size,equal to ImageMagick's -page size
		public var rW:Number=0;
		public var rH:Number=0;
		//Display area size
		public var dW:Number=0;
		public var dH:Number=0;
		//Percisely calculate the original relative offset value of Y axis.
		public function get oY():String
		{
			_oY = tY*(oH/dH)*usY;
			return _oY>=0?String("+").concat(_oY):String("-").concat(-_oY);
		}
		//Percisely calculate the original relative offset value of X axis.
		public function get oX():String
		{
			_oX = tX*(oW/dW)*usX;
			return _oX>=0?String("+").concat(_oX):String("-").concat(-_oX);
		}
		//Crop value for ImageMagick -crop,@see http://www.imagemagick.org/Usage/crop/#crop_viewport
		private var _cW:Number=0;//Crop width
		private var _cH:Number=0;//Crop height
		//Notice:crop image without quality loss as required.
		public function get cH():Number
		{
			//Ratio check
			_cH = dH/osY;
			//Too heighty with exception:
			var _eY:Number = (dH-rH) - tY*(oH/rH);
			_eY = (_eY>0)?_eY:0;
			_eY = (tY<0)?_eY*usY:0;
			//
			return (_cH + _eY);
		}
		//
		public function get cW():Number
		{
			//Ratio check
			_cW = dW/osX;
			//Too widthy with exception:
			var _eX:Number = (dW-rW) - tX*(oW/rW);
			_eX = (_eX>0)?_eX:0;
			_eX = (tX<0)?_eX*usY:0;
			//
			return (_cW + _eX);
		}
		//Page(viewPoint) value for ImageMagick -page,@see http://www.imagemagick.org/Usage/layers/#flatten
		private var _pW:Number=0;//Page view width
		private var _pH:Number=0;//Page view height
		public function get pH():Number
		{
			//Ratio check
			if(oW<=oH)
			{
				_pH = (oW * rH/rW);
			}else
			{
				_pH = oH;
			}
			
			return _pH;
		}
		//
		public function get pW():Number
		{
			//Ratio check
			if(oW<=oH)
			{
				_pW = oW;
			}else
			{
				_pW = (oW * rH/rW);
			}
			
			return _pW;
		}
		//ImageMagick -page offset values
		private var _pX:Number=0;//OffsetX
		private var _pY:Number=0;//OffsetY
		//
		public function get pY():String
		{
			//
			_pY = tY*(oH/dH);
			_pY -= opY;
			return _pY>=0?String("+").concat(_pY):_pY.toString();
		}
		public function get pX():String
		{
			//
			_pX = tX*(oW/dW);
			_pX -= opX;
			return _pX>=0?String("+").concat(_pX):String("-").concat(-_pX);
		}
		public function get opY():Number
		{
			return r!=0?(dH-rH)/2:0;
		}
		public function get opX():Number
		{
			return r!=0?(dW-rW)/2:0;
		}
		//ImageMagick -resize(zoomIn/Out) values
		public function get zH():Number
		{
			return oH*usY;
		}
		//
		public function get zW():Number
		{
			return oW*usX;
		}
		//ImageMagick -resize(zoomIn/Out) values
		public function get usX():Number
		{
			return dW/rW;
		}
		//
		public function get usY():Number
		{
			return dH/rH;
		}
		//For debugging
		public function toString():String
		{
			return ObjectUtil.toString(this);
		}
		
	}
}