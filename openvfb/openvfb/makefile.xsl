<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" />
<xsl:template match="/">
	<xsl:for-each select="module/implementation">
		<xsl:for-each select="source">
<xsl:value-of select="@path" />.o : <xsl:value-of select="@path" />.c ; $(CC) $(CFLAGS) -o $@ $(filter %.c,$+)
		</xsl:for-each>
	</xsl:for-each>
</xsl:template>
</xsl:stylesheet>