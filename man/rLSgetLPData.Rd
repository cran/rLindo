\name{rLSgetLPData}
\alias{rLSgetLPData}

\title{Retrieve the formulation data for a given linear 
       or mixed integer linear programming model.}

\description{
 R interface function for LINDO API function \code{LSgetLPData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetLPData(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnObjSense}{An integer indicating whether the objective is to be maximized or minimized.}
 \item{pdObjConst}{A double precision constant to be added to the objective value.}
 \item{padC}{A double array containing the linear program's objective coefficients.}
 \item{padB}{A double array containing the constraint right-hand side coefficients.}
 \item{pachConTypes}{A character array containing the type of each constraint.}
 \item{paiAcols}{An integer array containing the index of the first nonzero in each column.}
 \item{panAcols}{An integer array containing the length of each column.}
 \item{padAcoef}{A double array containing the nonzero coefficients of the constraint matrix.}
 \item{paiArows}{An integer array containing the row indices of the nonzeros in the constraint matrix.}
 \item{padL}{A double array containing the lower bound of each variable.}
 \item{padU}{A double array containing the upper bound of each variable.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadLPData}}
}