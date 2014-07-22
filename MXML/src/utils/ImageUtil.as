package utils
{
	import flash.display.BitmapData;
	import flash.geom.Matrix;

	public class ImageUtil
	{
		/**
		 * @private
		 * Utility function used for higher quality image scaling. Essentially we
		 * simply step down our bitmap size by half resulting in a much higher result
		 * though taking potentially multiple passes to accomplish.
		 * 
		 * source spark.primitives.BitmapImage
		 */
		public static function resample(bitmapData:BitmapData, newWidth:uint,
										   newHeight:uint, tx:Number,ty:Number,rotation:Number, quality:String = null):BitmapData
		{
			
			var finalScale:Number = Math.max(newWidth/bitmapData.width,
				newHeight/bitmapData.height);
			
			var finalData:BitmapData = bitmapData;
			
			// ERROR HERE MEANS
			// Property drawWithQuality not found on flash.display.BitmapData and there is no default value.
			// 
			// Solution
			// add -swf-version=16 or greater to your compiler arguments
			// 
			// https://bugbase.adobe.com/index.cfm?event=bug&id=3219149
			if (finalScale > 1)
			{
				finalData = new BitmapData(bitmapData.width * finalScale,
					bitmapData.height * finalScale, true, 0);
				
				if (quality) {
					finalData.drawWithQuality(bitmapData, new Matrix(finalScale, 0, 0,
						finalScale,tx,ty), null, null, null, true, quality);
				}
				else {
					finalData.draw(bitmapData, new Matrix(finalScale, 0, 0,
						finalScale,tx,ty), null, null, null, true);
				}
				
				return finalData;
			}
			
			var drop:Number = .5;
			var initialScale:Number = finalScale;
			
			while (initialScale/drop < 1)
				initialScale /= drop;
			
			var w:Number = Math.floor(bitmapData.width * initialScale);
			var h:Number = Math.floor(bitmapData.height * initialScale);
			var bd:BitmapData = new BitmapData(w, h, bitmapData.transparent, 0);
			
			if (quality) {
				bd.drawWithQuality(finalData, new Matrix(initialScale, 0, 0, initialScale,tx,ty),
					null, null, null, true, quality);
			}
			else {
				bd.draw(finalData, new Matrix(initialScale, 0, 0, initialScale,tx,ty),
					null, null, null, true);
			}
			
			finalData = bd;
			
			for (var scale:Number = initialScale * drop;
				Math.round(scale * 1000) >= Math.round(finalScale * 1000);
				scale *= drop)
			{
				w = Math.floor(bitmapData.width * scale);
				h = Math.floor(bitmapData.height * scale);
				bd = new BitmapData(w, h, bitmapData.transparent, 0);
				
				
				if (quality) {
					bd.drawWithQuality(finalData, new Matrix(drop, 0, 0, drop,tx,ty), null, null, null, true, quality);
				}
				else {
					bd.draw(finalData, new Matrix(drop, 0, 0, drop,tx,ty), null, null, null, true);
				}
				
				finalData.dispose();
				finalData = bd;
			}
			
			return finalData;
		}
	}
}