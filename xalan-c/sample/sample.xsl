<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output encoding="UTF-8" method="xml" />

	<xsl:template match="root-element"><translated-root><xsl:apply-templates /></translated-root></xsl:template>
	<xsl:template match="element1"><translated-element1><xsl:apply-templates /></translated-element1></xsl:template>
	<xsl:template match="element2"><translated-element2><xsl:apply-templates /></translated-element2></xsl:template>
	<xsl:template match="element3"><translated-element3><xsl:apply-templates /></translated-element3></xsl:template>
</xsl:stylesheet>
