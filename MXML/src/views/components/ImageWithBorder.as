
package views.components
{
	//--------------------------------------------------------------------------
	//
	// Imports
	//
	//--------------------------------------------------------------------------
	import mx.controls.Image;
	
	//BorderColor
	[Style(name="borderColor", type="uint", format="Color", inherit="no")]
	//BorderWidth
	[Style(name="borderWidth", type="Number", format="Length", inherit="no")]
	//BorderAlpha
	[Style(name="borderAlpha", type="Number", format="Length", inherit="no")]
	
	/**
	 * ImageWithBorder.as class. 
	 * @author yangboz
	 * @langVersion 3.0
	 * @playerVersion 11.2+
	 * @airVersion 3.2+
	 * Created Jul 15, 2014 4:08:53 PM
	 * @history 12/30/13,
	 */ 
	public class ImageWithBorder extends Image
	{ 
		//--------------------------------------------------------------------------
		//
		// Variables
		//
		//--------------------------------------------------------------------------
		
		//----------------------------------
		// CONSTANTS
		//----------------------------------
		
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
		public function ImageWithBorder()
		{
			super();
		} 
		//--------------------------------------------------------------------------
		//
		// Public methods
		//
		//--------------------------------------------------------------------------
		override protected function updateDisplayList(w:Number, h:Number):void{
			super.updateDisplayList(w,h);
			//
			if(width && height)
			{
				var x:Number=-(getStyle('borderWidth'));
				var y:Number=-(getStyle('borderWidth'));
				var width:Number=contentWidth+getStyle('borderWidth');
				var height:Number=contentHeight+getStyle('borderWidth');
//				graphics.clear();
//				graphics.lineStyle(getStyle('borderWidth'),getStyle('borderColor'),getStyle('borderAlpha'),false);
//				graphics.drawRect(x,y,width,height);
				//
				var dX:Number = x-1;
				var dY:Number = y-1;
				var dashy:DashedLine = new DashedLine(getStyle('borderWidth'),getStyle('borderColor'),new Array(2,2,2,2));
				dashy.moveTo(dX,dY);
				dashy.lineTo(width-dX,dY);
				dashy.lineTo(width-dX,height-dY);
				dashy.lineTo(dX,height-dY);
				dashy.lineTo(dX,dY);
				addChild(dashy);
			}
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
	}
	
}