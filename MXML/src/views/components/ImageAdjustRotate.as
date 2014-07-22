package views.components
{
	import spark.components.Image;
	
	public class ImageAdjustRotate extends Image
	{
		//
		public function ImageAdjustRotate()
		{
			super();
		}
		//
		override public function set rotation(value:Number):void
		{
			this.horizontalCenter = 0;
			this.verticalCenter = 0;
			//
			super.rotation = value;
			//
//			this.horizontalCenter = null;
//			this.verticalCenter = null;
		}
		//
	}
}