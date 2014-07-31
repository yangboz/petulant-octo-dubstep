package model
{
	import mx.utils.ObjectUtil;
	//
	public class ImageOprVO extends Object
	{
		public var sX:Number=1;//ScaleX
		public var sY:Number=1;//ScaleY
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
		//Required area size
		public var rW:Number=0;
		public var rH:Number=0;
		//Display area size
		public var dW:Number=0;
		public var dH:Number=0;
		//Percisely calculate the original relative offset value of Y axis.
		public function get oY():String
		{
			_oY = (rH-dH)/sY + tY*(rH/oH);
			return _oY>=0?String("+").concat(_oY):_oY.toString();
		}
		//Percisely calculate the original relative offset value of X axis.
		public function get oX():String
		{
			_oX = (rW-dW)/sX + tX*(rW/oW);
			return _oX>=0?String("+").concat(_oX):_oX.toString();
		}
		//Crop value for ImageMagick -crop
		private var _cW:Number=0;//Crop width
		private var _cH:Number=0;//Crop height
		//Notice:crop image without quality loss as required.
		public function get cH():Number
		{
			return oH;
			//Ratio check
			if(oW<=oH)
			{
				_cH = oW;//requiredW * contentH/contentW;
			}else
			{
				_cH = oH *(dH/rH);
			}
			
			return _cH;
		}
		//
		public function get cW():Number
		{
			return oW;
			//Ratio check
			if(oW<=oH)
			{
				_cW = oW *(dW/rW);
			}else
			{
				_cW = oH;//requiredH * contentW/contentH;
			}
			
			return _cW;
		}

		//
		public function toString():String
		{
			return ObjectUtil.toString(this);
		}
		
	}
}