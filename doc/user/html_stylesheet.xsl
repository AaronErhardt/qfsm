<?xml version='1.0'?> 

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0"> 
  <xsl:import href="/usr/share/xml/docbook/stylesheet/nwalsh5/current/html/docbook.xsl"/> 
  <xsl:param name="html.ignore.image.scaling" select="1"/> <!--doesn't work-->
  <xsl:template name="process.image.attributes"/> <!-- crude way. should work-->
</xsl:stylesheet> 

