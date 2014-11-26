<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" />
	<xsl:template match="/">
		<xsl:variable name="moduleId" select="translate(string(module/@id), '.', '_')" />
#define MODULE_ID <xsl:value-of select="$moduleId"/>

/* Provided interfaces */
	<xsl:for-each select="module/provides">
		<xsl:for-each select="directCall">
#define <xsl:value-of select="@name"/> <xsl:value-of select="$moduleId"/>_<xsl:value-of select="@name"/>
<xsl:value-of select="@returns"/><xsl:text> </xsl:text><xsl:value-of select="$moduleId"/>_<xsl:value-of select="@name"/>(<xsl:for-each select="arg">
<xsl:value-of select="@type"/><xsl:text> </xsl:text><xsl:value-of select="@name"/><xsl:if test="position() != last()">, </xsl:if></xsl:for-each>);
		</xsl:for-each>
	</xsl:for-each>

/* Required interfaces */
	<xsl:for-each select="module/requires">
		<xsl:for-each select="directCall">
#define <xsl:value-of select="@name"/> <xsl:value-of select="$moduleId"/>_<xsl:value-of select="@name"/>
extern <xsl:value-of select="@returns"/><xsl:text> </xsl:text><xsl:value-of select="$moduleId"/>_<xsl:value-of select="@name"/>(<xsl:for-each select="arg">
<xsl:value-of select="@type"/><xsl:text> </xsl:text><xsl:value-of select="@name"/><xsl:if test="position() != last()">, </xsl:if></xsl:for-each>);
		</xsl:for-each>
	</xsl:for-each>
	</xsl:template>
	
</xsl:stylesheet>