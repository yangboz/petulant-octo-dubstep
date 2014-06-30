////////////////////////////////////////////////////////////////////////////////
//
//  (c) 2011 Julius Loa | jloa@chargedweb.com | http://chargedweb.com/labs/
//  All Rights Reserved.
//  license:	MIT {http://www.opensource.org/licenses/mit-license.php}
//  notice: 	just keep the header plz
//
////////////////////////////////////////////////////////////////////////////////

package utils
{
	/** fp api **/	
	import flash.display.DisplayObject;
	import flash.text.TextField;
	import flash.geom.Rectangle;
	import flash.geom.Point;

	/**
	 * <p>AlignUtil class - vertical/horizontal align DisplayObjects</p>
	 * @availability 	fp9 (flash/flex, as3)
	 * @version 		1.3
	 *
	 * <p>Class usage:</p>
	 * @example using parentalRelation set to "true" (aligning children inside the "parent")
	 * <listing version="3.0">
	 * import com.chargedweb.utils.AlignUtil;
	 *
	 * var btn:Button = new Button();
	 * btn.x = 100;
	 * btn.y = 100;
	 * btn.width = 100;
	 * btn.height = 30;
	 * btn.rotation = 30;
	 * addChild(btn);
	 *
	 * AlignUtil.setAlign(AlignUtil.H_CENTER, btn, this);
	 * AlignUtil.setAlign(AlignUtil.V_MIDDLE, btn, this);
	 * </listing>
	 *
	 * @example using parentalRelation set to "false" (aligning children according to another child on the same level)
	 * <listing version="3.0">
	 * import flash.display.Shape;
	 * import com.chargedweb.utils.AlignUtil;
	 *
	 * function createBox(w:Number, h:Number, r:Number):Shape
	 * {
	 * 	var sp:Shape = new Shape();
	 *	sp.graphics.beginFill(Math.random()*0xffffff);
	 *	sp.graphics.drawRect(0, 0, w, h);
	 *	sp.graphics.endFill();
	 *	sp.rotation = r;
	 *	return sp;
	 * }
	 *
	 * var a:Shape = createBox(200, 200, 45);
	 * a.x = 200; a.y = 100;
	 * addChild(a);
	 *
	 * var b:Shape = createBox(50, 20, -10);
	 * b.x = 50; b.y = 200;
	 * addChild(b);
	 *
	 * var c:Shape = createBox(120, 75, 150);
	 * c.x = 300; c.y = 200;
	 * addChild(c);
	 *
	 * // align 'b','c' according to 'a' (horizontal-left and vertical-top alignment)
	 * // horizontally
	 * AlignUtil.setAlign(AlignUtil.H_LEFT, b, a, false);
	 * AlignUtil.setAlign(AlignUtil.H_LEFT, c, a, false);
	 * // now vertically
	 * AlignUtil.setAlign(AlignUtil.V_TOP, b, a, false);
	 * AlignUtil.setAlign(AlignUtil.V_TOP, c, a, false);
	 * </listing>
	 */
	public class AlignUtil
	{
		/** Horizontal left alignment **/
		public static const H_LEFT:String = "horizontalLeft";
		/** Horizontal center alignment **/
		public static const H_CENTER:String = "horizontalCenter";
		/** Horizontal right alignment **/
		public static const H_RIGHT:String = "horizontalRight";

		/** Vertical top alignment **/
		public static const V_TOP:String = "verticalTop";
		/** Vertical middle alignment **/
		public static const V_MIDDLE:String = "verticalMiddle";
		/** Vertical bottom alignment **/
		public static const V_BOTTOM:String = "verticalBottom";

		/**
		 * Applies a specified alignment to the target DisplayObject
		 * @param	align:String				alignment mode (see the public constants defined above)
		 * @param	target:DisplayObject		target DisplayObject to align (according to the set alignment mode) @see flash.display.DisplayObject
		 * @param	parent:DisplayObject		the parent DisplayObject of the target one @see flash.display.DisplayObject
		 * @param	parentalRelation:Boolean	whether the "target" DisplayObject is a child of the "parent" or not @default true;
		 * @return	nothing
		 */
		public static function setAlign(align:String, target:DisplayObject, parent:DisplayObject, parentalRelation:Boolean = true):void
		{
			var a:String = align;
			var t:DisplayObject = target;
			var p:DisplayObject = parent;
			var b:Rectangle = t.transform.pixelBounds;
			var tp:Point = new Point();
			var bp:Point;
			
			/**
			 * @note 28/03/2011 :: bug fix for TextFields :: tip by Arindam Mojumder <arindam.mojumder@gmail.com>
			 * TextField.transform.pixelBounds return incorrect x/y coordinates (not the actual, but rather
			 * the one of the transform point) and the x/y are always 'zero' valued, so we make an exception for tfs
			 */ 
			if(t is TextField) b = t.getBounds(t.parent);
				
			/** if parentalRelation is enabled, use local coordinates **/
			if(parentalRelation)
			{
				bp = p.globalToLocal(new Point(b.x, b.y));
				b.x = bp.x;	b.y = bp.y;
			}else{
				tp = new Point(p.transform.pixelBounds.x, p.transform.pixelBounds.y);
			}			
			
			if(a == H_LEFT) t.x = (t.x > b.x) ? tp.x + t.x - b.x : tp.x;
			if(a == H_CENTER) t.x = tp.x + int((p.width - b.width)/2 + t.x - b.x);
			if(a == H_RIGHT) t.x = (t.x > b.x + b.width) ? tp.x + p.width : tp.x + p.width - (b.x + b.width - t.x);
			if(a == V_TOP) t.y = (t.y > b.y) ? tp.y + t.y - b.y : tp.y;
			if(a == V_MIDDLE) t.y = tp.y + int((p.height - b.height)/2 + t.y - b.y);
			if(a == V_BOTTOM) t.y = (t.y > b.y + b.height) ? tp.y + p.height : tp.y + p.height - (b.y + b.height - t.y);
		}
	}
}