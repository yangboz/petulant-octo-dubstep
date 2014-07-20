
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
		private var dashy:DashedLine;
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
				var width:Number=contentWidth-getStyle('borderWidth');
				var height:Number=contentHeight-getStyle('borderWidth');
//				graphics.clear();
//				graphics.lineStyle(1,getStyle('borderColor'),getStyle('borderAlpha'),false);
//				graphics.drawRect(x,y,width,height);
				//
				var dX:Number = getStyle('borderWidth');
				var dY:Number = getStyle('borderWidth');
				if(this.dashy)
				{
					this.removeChild(dashy);
				}
				this.dashy = new DashedLine(0.5,getStyle('borderColor'),new Array(2,2,2,2));
				dashy.moveTo(-dX,-dY);
				dashy.lineTo(width+2*dX,-dY);
				dashy.lineTo(width+2*dX,height+2*dY);
				dashy.lineTo(-dX,height+2*dY);
				dashy.lineTo(-dX,-dY);
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