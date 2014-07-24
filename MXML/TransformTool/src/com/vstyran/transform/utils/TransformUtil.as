package com.vstyran.transform.utils
{
	import com.vstyran.transform.model.DisplayData;
	
	import flash.display.DisplayObject;
	import flash.geom.Matrix;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	
	import mx.core.UIComponent;
	import mx.utils.MatrixUtil;
	
	/**
	 * Utility class that has methods for transformation.
	 * 
	 * @author Volodymyr Styranivskyi
	 */
	public class TransformUtil
	{
		/**
		 * Create transformation matrix from source panel to destination panel.
		 *  
		 * @param sourceContext Source coordinate space. If null then stage will be used.
		 * @param destContext Destination coordinate space. If null then stage will be used.
		 * @return transform matrix
		 */		
		public static function getMatrix(sourceContext:DisplayObject, destContext:DisplayObject):Matrix
		{
			var m:Matrix = new Matrix();
			
			if(sourceContext)
				m = MatrixUtil.getConcatenatedMatrix(sourceContext, null);
			
			if(destContext)
			{
				var dm:Matrix = new Matrix();
				dm = MatrixUtil.getConcatenatedMatrix(destContext, null);
				dm.invert();
				m.concat(dm);
			}
			
			return m;
		}
		
		/**
		 * Transform data. Original data object will not be changed.
		 *  
		 * @param m Transformation matrix.
		 * @param sourceData Data that will be transformed.
		 * @return Transformed data.
		 * 
		 */		
		public static function transformData(m:Matrix, sourceData:DisplayData):DisplayData
		{
			var data:DisplayData = new DisplayData();
			
			var position:Point = m.transformPoint(new Point(sourceData.x, sourceData.y));
			data.x = position.x;
			data.y = position.y;
			
			var components:Vector.<Number> = new Vector.<Number>(4);
			MatrixUtil.decomposeMatrix(components,m);
			
			data.width = sourceData.width* components[3];
			data.height = sourceData.height*components[4];
			data.rotation = components[2]+sourceData.rotation;
			
			data.minWidth = !isNaN(sourceData.minWidth) ? sourceData.minWidth * components[3] : NaN;
			data.minHeight = !isNaN(sourceData.minHeight) ? sourceData.minHeight * components[4] : NaN; 
			data.maxWidth = !isNaN(sourceData.maxWidth) ? sourceData.maxWidth * components[3] : NaN; 
			data.maxHeight = !isNaN(sourceData.maxHeight) ? sourceData.maxHeight * components[4] : NaN;
			
			return data;
		}
	}
}